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
  Serial.println("Dados recebidos!");
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

  dataReceivedFlag = true;
}



void setup() {
  Serial.begin(115200);
}

void loop() {
  // Ativa o ESP-NOW para aguardar dados
  Serial.println("Ativando ESP-NOW...");
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao ativar ESP-NOW");
    return;
  }

  // Registra a função de callback para recepção de dados via ESP-NOW
  esp_now_register_recv_cb(OnDataRecv);

  // Aguarda os dados serem recebidos (fica nesse loop até receber algo)
  while (!dataReceivedFlag) {
    Serial.println("Aguardando dados via ESP-NOW...");
    delay(1000);
  }

  // Desativa o ESP-NOW após os dados serem recebidos
  Serial.println("Desligando ESP-NOW...");
  esp_now_deinit();

  // Conecta ao Wi-Fi para enviar os dados via HTTP
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Aguardando conexão ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Envia os dados ao servidor HTTP
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // URL do servidor
    http.begin("http://192.168.246.34:8000");  // Substitua pela sua URL

    // Definir cabeçalhos
    http.addHeader("Content-Type", "application/json");

    // Corpo da requisição (JSON com os dados recebidos via ESP-NOW)
    String jsonBody = "{\"device_id\":\"32\", \"temperature\":\"" + String(dataReceived.message) + "\", \"humidity\":" + String(dataReceived.value) + "}";

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
  Serial.println("Desconectando do WiFi...");
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  delay(1000);

  // Reseta o flag de recebimento para reiniciar o ciclo
  dataReceivedFlag = false;
}
