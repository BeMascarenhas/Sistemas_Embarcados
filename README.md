# Sistemas_Embarcados 🔥

### R 1. Sensores
- **Sensor de Umidade e Temperatura (DHT11 ou DHT22):** Para medir a umidade relativa e a temperatura ambiente.
- **Sensor de Fumaça (MQ-2 ou MQ-135):** Para detectar a presença de gases e fumaça no ambiente.

### R 2. Plataforma e Processamento
- **Placa Arduino (UNO, 2560, ou outra):** A placa principal para processamento dos dados dos sensores.
- **Fonte de Alimentação:** Bateria ou fonte de alimentação externa para fornecer energia ao Arduino e aos sensores.

### R 3. Comunicação
- **Módulo de Comunicação (ESP8266 ou ESP32):** Para enviar os dados coletados para uma central que trata e armazena os dados em nuvem.

### R 4. Software
- **IDE Arduino:** Para escrever, compilar e carregar o código no Arduino.
- **Bibliotecas:**
  - **DHT:** Para lidar com os dados do sensor de umidade e temperatura.
  - **MQ2/MQ135:** Para lidar com os dados do sensor de fumaça.
- **Algoritmo de Monitoramento:** Código para leitura contínua dos sensores e alerta em caso de valores fora do normal (alta temperatura, baixa umidade, presença de fumaça).

### R 5. Estrutura Física
- **Caixa de Proteção:** Para abrigar o Arduino, sensores e demais componentes, protegendo-os de danos externos e facilitando a instalação em áreas externas.

### R 6. Considerações Adicionais
- **Testes de Campo:** Realizar testes em ambientes controlados para validar a eficácia do sistema em detectar condições de risco.

### R 7. Objetivo do projeto
- Criar um sistema para prevenir incêndios de se agravarem em áreas de risco, identificando o foco e o início do incêndio.

