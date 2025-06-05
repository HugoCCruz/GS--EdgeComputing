# :ocean: Aqua Sensors

 
### Sistema de Controle de Enchentes com Arduino
Este projeto utiliza um sistema automatizado com Arduino para detectar e controlar o nível da água em ambientes residenciais, com o objetivo de prevenir alagamentos. 

 

## :pencil: Descrição do Problema 

 

Uma enchente em uma residência causa diversos prejuízos e transtornos. A água pode danificar a estrutura da casa, como pisos, paredes, eletrodomésticos e móveis. Além disso, a presença de água contaminada representa riscos à saúde, com possibilidade de doenças como leptospirose, hepatite A e infecções respiratórias causadas por mofo. 

 

Para isso, criamos um sistema automatizado com Arduino que detecta o nível da água em determinado ponto (como uma garagem ou piso baixo) e, ao atingir certo limite, aciona um mecanismo para abrir ralos ou fechar comportas, permitindo que a água seja drenada e evitando que o problema se torne mais grave. 

 

--- 

 

## :bulb: Visão Geral da Solução 

 

O sistema monitora o nível da água em tempo real utilizando sensores. Quando o nível água atinge um valor considerado alto, o Arduino envia um sinal para um servo motor, que aciona um ralo e caso atinja um nível crítico aciona uma comporta. Isso permite que a água seja escoada automaticamente e bloqueie a entrada da mais agua do ambiente externo, prevenindo alagamentos. 

 

## :wrench: Componentes Utilizados 

 

 **Placa principal**

 - Arduino UNO 

   Microcontrolador responsável por ler os sensores, controlar os atuadores e processar os dados. 

 

 **Sensores**

 

 - DHT22 (Sensor de temperatura e umidade) 

   Mede a temperatura e a umidade do ambiente. Está conectado a um pino digital do Arduino (possivelmente D2) e utiliza um resistor pull-up. 

 

 - HC-SR04 (Sensor ultrassônico de distância) 

    Mede a distância por meio de ondas ultrassônicas. Possui quatro pinos: VCC, GND, Trig e Echo. Os pinos de sinal estão conectados aos pinos digitais do Arduino. 

 

**Indicadores** 

 

 - LEDs (3 unidades: vermelho, amarelo e verde) 

   Servem como indicadores visuais de status ou níveis. Cada LED está conectado em série com um resistor limitador de corrente. 
 

**Atuador**

 

 - Servo motor 

   Executa movimentos angulares. Está conectado à alimentação e a um pino PWM do Arduino. 

 

**Saída visual**

 

 - Display LCD 16x2 com módulo I2C 

   Exibe informações como temperatura, umidade e distância. Está conectado ao Arduino via interface I2C (pinos SDA e SCL, correspondentes aos pinos A4 e A5 no Arduino UNO). **

---

 

## :gear: Funcionamento 

1. O sensor DHT22 detecta o nível de umidade do ambiente. Os leds respondem a esse sensor. 

2. O sensor de nível detecta a altura da água. 

3. Quando o nível ultrapassa o valor configurado, o Arduino aciona o servo motor. 

4. O ralo se abre automaticamente, permitindo a drenagem. 

5. Caso o ralo não esteja conseguindo drenar e o nível chegue à crítico, uma comporta é fechada. 

6. O sistema pode retornar ao estado inicial quando o nível se normaliza.

   
## :test_tube: Simulação no Wokwi 

 
https://wokwi.com/projects/432413696310358017 


## :electric_plug:Diagrama de Conexão

| Componente      | Pino Arduino      |
|-----------------|-------------------|
| DHT22 Data      | 2                 |
| LED Verde       | 11                |
| LED Amarelo     | 10                |
| LED Vermelho    | 9                 |
| ServoMotor1     | 5                 |
| ServoMotor2     | 8                 |
| HC-SR04 Trigger | 6                 |
| HC-SR04 Echo    | 7                 |
| LCD I2C SDA     | A4 (ou SDA)       |
| LCD I2C SCL     | A5 (ou SCL)       |

## 📚 Biblioteca

- DHT sensor library
- Adafruit Unified Sensor
- LiquidCrystal I2C
- Servo


 



 
