#define PIN_TRIG D6 // ПИН D7
#define PIN_ECHO D5 // ПИН D6
long duration, cm;
void setup() {
  Serial.begin (9600); // Устанавливаем сокорость соединения с последовательным портом
  pinMode(PIN_TRIG, OUTPUT); // Определяем вывод

}
void loop() {
  // Создаем короткий импульс длительностью 5 микросекунд.
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  // Установим высокий уровень сигнала
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  //  Определяем задержку сигнала
  duration = pulseIn(PIN_ECHO, HIGH);
  // Преобразуем время задержки в расстояние
  cm = (duration / 2) / 29.1;
  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");
  // Задержка между измерениями
  delay(250);
}