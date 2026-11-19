#define MQ135_PIN A0  // Пин, к которому подключен MQ-135
#define BUZZER_PIN 9   // Пин, к которому подключена пьезопищалка
#define THRESHOLD 300  // Пороговое значение газа для срабатывания тревоги

void setup() {
    pinMode(MQ135_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int gasValue = analogRead(MQ135_PIN);
    Serial.print("Gas Value: ");
    Serial.println(gasValue);
    
    if (gasValue > THRESHOLD) {
        tone(BUZZER_PIN, 2000); // Включаем звук на 2000 Гц
        Serial.println("Fire detected! Alarm ON!");
    } else {
        noTone(BUZZER_PIN); // Выключаем звук
    }
    
    delay(1000); // Задержка в 1 секунду перед следующим измерением
}
