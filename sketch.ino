#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

// === LCD ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Pinos ===
#define trigger 6 
#define echo 7
#define ledR 9
#define ledY 10
#define ledG 11
#define servoPin 5
#define DHTPIN 2
#define DHTTYPE DHT22

Servo servo;

// === Objetos e variáveis ===
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS = 2000;

unsigned long previousDHTMillis = 0;
unsigned long previousLCDMillis = 0;

float umidade = 0;
int anguloServo = 0;
long duracao;
float distancia;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  servo.attach(servoPin);
  dht.begin();

  sensor_t sensor;
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");
  delay(1000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // === Leitura do DHT11 ===
  if (currentMillis - previousDHTMillis >= delayMS) {
    previousDHTMillis = currentMillis;

    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (!isnan(event.relative_humidity)) {
      umidade = event.relative_humidity;
    } else {
      Serial.println("Erro na leitura de umidade!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Erro leitura DHT");
      lcd.setCursor(0, 1);
      lcd.print("Ver sensor!");
      delay(2000);
      return; // Interrompe o loop até próxima leitura
    }
  }

  // === Atualização do LCD ===
  if (currentMillis - previousLCDMillis >= 2000) {
    previousLCDMillis = currentMillis;
    lcd.clear();

    Serial.print("Umidade: ");
    Serial.print(umidade, 1);
    Serial.println(" %");

    if (umidade < 45) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade BAIXA");
      lcd.setCursor(0, 1);
      lcd.print("Umid: ");
      lcd.print(umidade, 1);
      lcd.print("%");

      digitalWrite(ledR, HIGH);
      digitalWrite(ledY, LOW);
      digitalWrite(ledG, LOW);
      anguloServo = 0;  // Ralo fechado
    }
    else if (umidade <= 70) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade OK");
      lcd.setCursor(0, 1);
      lcd.print("Umid: ");
      lcd.print(umidade, 1);
      lcd.print("%");

      digitalWrite(ledR, LOW);
      digitalWrite(ledY, HIGH);
      digitalWrite(ledG, LOW);
      anguloServo = 0;  // Ralo fechado
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("Umidade ALTA");
      lcd.setCursor(0, 1);
      lcd.print("Checando agua...");

      digitalWrite(ledR, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledG, HIGH);

      distancia = medirDistancia();
      Serial.print("Distancia: ");
      Serial.print(distancia);
      Serial.println(" cm");

      if (distancia < 10) {
        anguloServo = 90; // Abrir ralo
        lcd.setCursor(0, 1);
        lcd.print("Ralo ABERTO!   ");
      } else {
        anguloServo = 0; // Fechar ralo
        lcd.setCursor(0, 1);
        lcd.print("Nivel normal   ");
      }
    }

    servo.write(anguloServo);
  }

  delay(100);
}

// === Função para medir distância ===
float medirDistancia() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duracao = pulseIn(echo, HIGH, 30000);  // timeout 30ms
  float distanciaCm = duracao * 0.034 / 2;
  return distanciaCm;
}