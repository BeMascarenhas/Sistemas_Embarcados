## Introdução do artigo
O monitoramento e controle de ambientes geograficamente isolados representa um desafio significativo, especialmente em contextos onde a infraestrutura de conectividade é limitada ou inexistente. A preservação ambiental e a mitigação de desastres naturais são questões críticas, e o desenvolvimento de soluções tecnológicas para monitorar essas áreas pode ter um impacto significativo na gestão de riscos. Tecnologias emergentes têm desempenhado um papel crucial na abordagem desses desafios, proporcionando soluções inovadoras e acessíveis (Niemeyer et al., 2020; Al-Khateeb et al., 2019).

Um campo de aplicação particularmente relevante é a prevenção de queimadas, que requer um monitoramento eficaz de parâmetros ambientais como temperatura, umidade e concentração de gases nocivos (Smith et al., 2021). A detecção precoce de condições que favorecem a deflagração de incêndios pode ser crucial para minimizar danos e proteger ecossistemas e comunidades. Estudos mostram que sistemas de sensores embarcados podem fornecer uma solução eficaz para monitoramento em áreas remotas (Zhao et al., 2021; Kim et al., 2022).

O protocolo ESP-NOW tem sido recentemente explorado para comunicação em redes de sensores devido à sua capacidade de operar sem a necessidade de uma conexão contínua com a internet, facilitando a comunicação entre dispositivos em locais isolados (Chen et al., 2021). Complementarmente, o protocolo MQTT é amplamente utilizado para a transmissão de dados em tempo real, oferecendo uma plataforma eficiente para a integração de dados com a nuvem e análise em tempo real (Liu et al., 2020; Johnson et al., 2019).

Este artigo propõe o desenvolvimento de um sistema baseado nessas tecnologias para monitoramento e controle de áreas isoladas, focando na prevenção de queimadas. Utilizando o protocolo ESP-NOW para comunicação local entre dispositivos e MQTT para transmissão de dados para a nuvem, buscamos criar uma solução que permita a detecção precoce de condições de risco e a geração de alertas automáticos. O objetivo é avaliar a eficácia dessa abordagem na mitigação de desastres ambientais e na proteção de áreas de difícil acesso.

Esp32 - https://eprints.uklo.edu.mk/id/eprint/6312/ 
Mqtt - https://ieeexplore.ieee.org/abstract/document/9108808 
Incendio - https://ieeexplore.ieee.org/abstract/document/7074110 

Na Seção II, discutimos a abordagem proposta para a implementação de um sistema de monitoramento de queimadas, detalhando o uso dos protocolos ESP-NOW e MQTT para comunicação e transmissão de dados. Na Seção III, descrevemos a configuração dos protótipos dos dispositivos de monitoramento e os sensores utilizados para a coleta de dados ambientais. Na Seção IV, apresentamos os resultados obtidos dos testes realizados, avaliando a eficácia do sistema na detecção ágil de condições de risco e discutindo os desafios enfrentados durante a implementação. Finalmente, na Seção V, concluímos o estudo com uma análise das contribuições do sistema para a mitigação de desastres ambientais e sugerimos direções para pesquisas futuras.

### Placas Esp-32

As placas ESP32 possibilitam uma transmissão de dados eficiente sem a necessidade de conexão Wi-Fi, utilizando os protocolos ESP-NOW e MQTT. A combinação desses protocolos permite a criação de uma rede de baixo custo e fácil implementação, adequando-se bem a aplicações em ambientes remotos. No entanto, essa abordagem apresenta algumas limitações significativas: o alcance da comunicação é restrito a um máximo de 450 metros, e a capacidade de transmissão de dados é limitada a 250 bytes por pacote. Essas restrições devem ser consideradas ao projetar sistemas que dependem de redes de sensores baseadas em ESP32, pois podem impactar a abrangência e a quantidade de dados transmitidos em aplicações de monitoramento e controle. 

### Sensores

Para os testes de detecção de incêndios, utilizamos os sensores DHT11, para medir umidade e temperatura, e o sensor MQ7, para monitorar a concentração de monóxido de carbono. Esses sensores permitem a análise de três parâmetros cruciais—umidade, temperatura e níveis de monóxido de carbono—visando a detecção precoce de incêndios e a minimização de alarmes falsos. O DHT11 é eficiente na detecção dentro de um raio de até 20 metros, o que se mostrou adequado para o escopo dos nossos testes. A integração desses sensores com o sistema de comunicação previamente descrito viabiliza a formação de uma rede que pode monitorar e identificar precocemente a ocorrência de incêndios em áreas específicas. Contudo, a precisão e a confiabilidade do sistema dependem fortemente da calibração adequada e do correto posicionamento dos sensores, aspectos essenciais para assegurar a eficácia na detecção e a redução de alarmes falsos. 

### Possiveis Citações:
Deploying an ESP32-based two-way communication system has a big impact on the
effectiveness, dependability, and expandability of Internet of Things (IoT) systems. 
@article{madhukumar2024esp,
  title={ESP-NOW based Two Way Data Transferring},
  author={MadhuKumar, V and Sree, N Suma and Priya, S and Sai, A Vivek and Eshwar, K and Nagaraju, S},
  journal={RES MILITARIS},
  volume={14},
  number={4},
  pages={238--248},
  year={2024}
}
