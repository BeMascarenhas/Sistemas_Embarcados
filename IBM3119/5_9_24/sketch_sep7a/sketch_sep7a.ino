#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_now.h>
#include <ArduinoJson.h>

// Informações de conexão Wi-Fi
const char* ssid = "Alex S20";       // Substitua pelo seu SSID
const char* password = "15010201";   // Substitua pela sua senha

// Estrutura para receber dados via ESP-NOW
typedef struct struct_message {
  char message[50];
  int value;
} struct_message;

struct_message dataReceived;

// Variável de controle para indicar que os dados foram recebidos
bool dataReceivedFlag = false;

// Função de callback para receber dados via ESP-NOW
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&dataReceived, incomingData, sizeof(dataReceived));

  Serial.print("Dados recebidos de: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(recv_info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  
  Serial.print("Mensagem: ");
  Serial.println(dataReceived.message);
  Serial.print("Valor: ");
  Serial.println(dataReceived.value);

  // Marca que os dados foram recebidos
  dataReceivedFlag = true;
}

void setup() {
  Serial.begin(115200);

  // Configura o modo Wi-Fi como estação
  WiFi.mode(WIFI_STA);

  // Inicializa o ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  // Registra a função de callback para recepção de dados via ESP-NOW
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Verifica se os dados foram recebidos via ESP-NOW
  if (dataReceivedFlag) {
    // Desliga o ESP-NOW antes de conectar ao Wi-Fi
    Serial.println("Desligando ESP-NOW...");
    esp_now_deinit();  // Desativa o ESP-NOW

    // Conectar ao Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi");

    // Enviar dados ao servidor HTTP
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // URL do servidor
      http.begin("http://192.168.96.34:8000");  // Substitua pela sua URL

      // Definir cabeçalhos
      http.addHeader("Content-Type", "application/json");

      // Corpo da requisição (JSON com os dados recebidos via ESP-NOW)
      String jsonBody = "{\"device_id\":\"ESP32\", \"message\":\"" + String(dataReceived.message) + "\", \"value\":" + String(dataReceived.value) + "}";

      // Enviar requisição POST
      int httpResponseCode = http.POST(jsonBody);

      // Verificar resposta
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Código de resposta: " + String(httpResponseCode));
        Serial.println("Resposta: " + response);
      } else {
        Serial.print("Erro na requisição: ");
        Serial.println(httpResponseCode);
      }

      // Finalizar a conexão HTTP
      http.end();
    }

    // Desconectar do Wi-Fi para economizar energia
    WiFi.disconnect();
    Serial.println("Desconectado do WiFi.");

    // Reativar o ESP-NOW para continuar recebendo dados
    Serial.println("Reativando ESP-NOW...");
    if (esp_now_init() != ESP_OK) {
      Serial.println("Erro ao reativar ESP-NOW");
    } else {
      Serial.println("ESP-NOW ativado novamente");
    }

    // Reseta o flag de recebimento para aguardar novos dados
    dataReceivedFlag = false;
  }

  // Delay para evitar polling intenso
  delay(500);
}
