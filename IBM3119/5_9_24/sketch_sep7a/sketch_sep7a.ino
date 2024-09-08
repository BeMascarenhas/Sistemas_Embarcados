#include <WiFi.h>
#include <PubSubClient.h>

// Configurações da rede Wi-Fi
const char *ssid = "";
const char *password = "";

// Configurações do broker MQTT
const char *mqtt_broker = "";  // IP do broker
const int mqtt_port = 1883;                // Porta do broker
const char *mqtt_topic = "test/topic";     // Tópico onde a mensagem será publicada

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);

    // Conectar-se ao Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado ao Wi-Fi!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // Configurar o servidor MQTT
    client.setServer(mqtt_broker, mqtt_port);

    // Tentar conectar ao broker MQTT
    connectToMQTT();
}

void loop() {
    if (!client.connected()) {
        connectToMQTT();  // Tentar reconectar se desconectado
    }
    client.loop();

    // Publicar a cada 10 segundos
    static unsigned long lastMsgTime = 0;
    if (millis() - lastMsgTime > 10000) {  // A cada 10 segundos
        lastMsgTime = millis();
        publishMessage();  // Função para realizar o publish
    }
}

// Função para conectar ao broker MQTT
void connectToMQTT() {
    Serial.println("Tentando conectar ao broker...");

    while (!client.connected()) {
        if (client.connect("esp32-client")) {
            Serial.println("Conectado ao broker");
            client.subscribe(mqtt_topic);  // Subscrevendo ao tópico
            Serial.println("Subscrevendo ao tópico: test/topic");
        } else {
            Serial.print("Falha ao conectar ao broker, estado: ");
            Serial.println(client.state());
            delay(5000);  // Esperar 5 segundos antes de tentar reconectar
        }
    }
}

// Função para publicar uma mensagem no broker
void publishMessage() {
    const char *message = "Hello from ESP32";
    Serial.print("Publicando mensagem: ");
    Serial.println(message);
    
    // Publicar a mensagem no tópico
    if (client.publish(mqtt_topic, message)) {
        Serial.println("Mensagem publicada com sucesso");
    } else {
        Serial.println("Falha ao publicar a mensagem");
    }
}
