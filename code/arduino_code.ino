// Smart Plant Monitoring System - Arduino Code

#include <DHT.h>

#define SOIL_PIN A0
#define LDR_PIN  A1
#define RELAY_PIN 7
#define LED_PIN 13
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int soilThreshold = 500;
int lightThreshold = 500;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  dht.begin();
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);
  int ldrValue = analogRead(LDR_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Soil: "); Serial.print(soilValue);
  Serial.print(" | LDR: "); Serial.print(ldrValue);

  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print(" | Temp: "); Serial.print(temperature);
    Serial.print("°C | Hum: "); Serial.print(humidity); Serial.print("%");
  }

  Serial.println();

  if (soilValue > soilThreshold) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Motor ON (Dry Soil)");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Motor OFF (Wet Soil)");
  }

  if (ldrValue < lightThreshold) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Light ON (Dark)");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Light OFF (Bright)");
  }

  Serial.println("================================");
  delay(10000);
}
