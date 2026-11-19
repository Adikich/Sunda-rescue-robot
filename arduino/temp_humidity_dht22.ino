#include <DHT.h>

#define DHTPIN 12       // Подключен к цифровому пину D12
#define DHTTYPE DHT22   // Тип датчика DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float humidity = dht.readHumidity();      // Читаем влажность
    float temperature = dht.readTemperature(); // Читаем температуру в Цельсиях

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Ошибка считывания с датчика!");
        return;
    }

    Serial.print("Влажность: ");
    Serial.print(humidity);
    Serial.print("%  Температура: ");
    Serial.print(temperature);
    Serial.println("°C");

    delay(2000);  // Читаем данные каждые 2 секунды
}
