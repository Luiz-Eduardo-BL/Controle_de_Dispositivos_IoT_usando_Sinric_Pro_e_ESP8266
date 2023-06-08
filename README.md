# Controle de Dispositivos IoT usando Sinric Pro e ESP8266

Este é um projeto que permite controlar uma lâmpada remotamente usando o Sinric Pro e exibir a temperatura. O projeto utiliza a placa ESP8266 e os seguintes componentes: 
- lâmpada, 
- sensor de temperatura DHT11

## Instalação

Siga as instruções abaixo para configurar o ambiente de desenvolvimento, instalar as bibliotecas necessárias e realizar as conexões corretas dos componentes.

### Configurando o Ambiente de Desenvolvimento

1. Baixe e instale o Arduino IDE no seu computador, caso ainda não tenha: [Arduino IDE](https://www.arduino.cc/en/software)

2. Conecte a placa ESP8266 ao seu computador via cabo USB.

3. Abra o Arduino IDE e vá em **Arquivo > Preferências**.

4. No campo "URLs adicionais para Gerenciadores de Placas", adicione a seguinte URL:
  
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```

5. Clique em OK para fechar as preferências.

6. Vá em **Ferramentas > Placa > Gerenciador de Placas**.

7. Na caixa de busca, digite "esp8266".

8. Selecione "esp8266 by ESP8266 Community" e clique em "Instalar".

9. Aguarde até que a instalação esteja concluída.

### Instalando as Bibliotecas

1. Abra o Arduino IDE.

2. Vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.

3. Na caixa de busca, digite o nome da biblioteca e clique em "Instalar" para cada uma delas:
- SinricPro: biblioteca oficial do Sinric Pro.
- DHT: biblioteca para o sensor de temperatura DHT11.

4. Aguarde até que a instalação de todas as bibliotecas esteja concluída.

### Conexões dos Componentes

Conecte os componentes conforme as seguintes conexões:

- Conecte a lâmpada ao pino digital 5 (Lampada_Pin) da placa ESP8266.
- Conecte o sensor de temperatura DHT11 ao pino digital 2 (DHT_PIN) da placa ESP8266.

Certifique-se de seguir as especificações do fabricante para cada componente.

### Configurando as Credenciais do Sinric Pro

1. Acesse o site do Sinric Pro em [https://sinric.pro/](https://sinric.pro/) e crie uma conta, caso ainda não tenha uma.

2. Faça login na sua conta do Sinric Pro.

3. Crie um novo dispositivo para a lâmpada no Sinric Pro. Anote o ID do dispositivo gerado.

4. Copie a chave do aplicativo (APP_KEY) e a senha do aplicativo (APP_SECRET) disponíveis na página de credenciais do Sinric Pro.

### Configurando o Projeto

1. Conecte a lâmpada e os demais componentes conforme as conexões descritas anteriormente.

2. Abra o Arduino IDE.

3. Crie um novo sketch.

4. Copie o código fornecido neste repositório para o Arduino IDE.

5. Substitua as informações necessárias no código:
- WIFI_SSID: insira o nome da sua rede Wi-Fi.
- WIFI_PASS: insira a senha da sua rede Wi-Fi.
- APP_KEY: insira a chave do aplicativo do Sinric Pro.
- APP_SECRET: insira a senha do aplicativo do Sinric Pro.
- Lampada_ID: insira o ID do dispositivo lâmpada criado no Sinric Pro.

6. Compile e envie o código para a placa ESP8266.

### Utilizando o Projeto

Após a configuração e upload do código para a placa ESP8266, o projeto estará pronto para uso.

A placa ESP8266 estabelecerá uma conexão Wi-Fi com a sua rede e se conectará à nuvem do Sinric Pro. A lâmpada poderá ser controlada remotamente através do aplicativo Sinric Pro. Além disso, a temperatura será medida pelo sensor DHT11.

## Avisos

- Certifique-se de seguir corretamente as instruções de conexão e configuração do projeto.
- Este projeto requer uma conexão Wi-Fi estável para se comunicar com a nuvem do Sinric Pro e receber comandos de controle remoto.
- Verifique se a lâmpada e os demais componentes estão corretamente conectados e funcionando adequadamente.
- A temperatura medida pelo sensor DHT11 pode não ser totalmente precisa. Certifique-se de calibrar e testar o sensor de acordo com as especificações do fabricante.

## Resolução de problemas

Se encontrar problemas ao configurar ou utilizar o projeto, siga as etapas abaixo:

1. Verifique se todas as conexões dos componentes estão corretas.
2. Verifique se as bibliotecas foram instaladas corretamente no Arduino IDE.
3. Verifique se as credenciais do Sinric Pro foram inseridas corretamente no código.
4. Verifique se a placa ESP8266 está corretamente selecionada no Arduino IDE.
5. Verifique se a sua rede Wi-Fi está funcionando corretamente e se a placa ESP8266 está conectada a ela.
6. Verifique se a lâmpada e os demais componentes estão funcionando adequadamente.

Se os problemas persistirem, consulte a documentação do fabricante para obter suporte adicional ou procure ajuda em fóruns e comunidades online relacionadas ao Arduino e ao Sinric Pro.

