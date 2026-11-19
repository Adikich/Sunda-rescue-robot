#include <DHT.h>

#define DHTPIN 3          // Пин датчика DHT22
#define DHTTYPE DHT22     // Тип датчика DHT22
DHT dht(DHTPIN, DHTTYPE);

#define FLAME_SENSOR A1   // KY-026 (A0 или D0)
#define BUZZER 4          // Пассивная пьезопищалка

void setup() {
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  int flame = digitalRead(FLAME_SENSOR);  // 0 = огонь обнаружен
  float temp = dht.readTemperature();     // Читаем температуру

  Serial.print("Flame: ");
  Serial.print(flame);
  Serial.print(" | Temperature: ");
  Serial.println(temp);

  if (flame == 0 || temp > 50) { // Если есть пламя или высокая температура
    tone(BUZZER, 1000);  // Включить пищалку (1000 Гц)
             // Ждем 2 сек
  }

  delay(500); // Маленькая задержка для снижения нагрузки
}
