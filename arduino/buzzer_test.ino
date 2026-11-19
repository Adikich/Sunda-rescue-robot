#define BUZZER_PIN 9

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    tone(BUZZER_PIN, 2000);  // Генерируем звук 2000 Гц
    delay(1000);
    noTone(BUZZER_PIN);  // Выключаем звук
    delay(1000);
}
