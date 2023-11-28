#define PIN_TRIG 2
#define PIN_ECHO 3
#define LED_OK 7
#define LED_BAD 6

long duration, cm;

int min = 0;
int max = 0;
double* vals;
bool is_showed = false;

void setup() {

  // Инициализируем взаимодействие по последовательному порту

  Serial.begin (9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_BAD, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(LED_BAD, LOW);
  digitalWrite(LED_OK, LOW);
}

void loop() {

  // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.
  if (min == 0 || max == 0) {
    Serial.println("Введите диапазон:");
    while (min == 0) {
      if (Serial.available() > 0) {
        min = Serial.parseInt();
      }
    }
    while (max == 0) {
      if (Serial.available() > 0) {
        max = Serial.parseInt();
      }
    }

    vals = new double[max - min];
    for (int i = 0; i < max - min; i++) {
      vals[i] = 0;
    }
    
  } else {
    work();
  }
}


void work() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;

  if (check_is_enough()) {
    if (!is_showed) {
      show_ok();
      send_mess();
      is_showed = true;
    }
  } else {
    show_bad();
    if (cm >= min && cm <= max) {
    double val = analogRead(A0);
    val = val * 5.0 / 2046.0;
    vals[cm - min] = val;
    
    Serial.print("Расстояние до объекта: ");
    Serial.print(cm);
    Serial.print(" см. ");
    Serial.println(val);
    // for (int i = 0; i < max - min; i++) {
    //   Serial.print(i + min);
    //   Serial.print(" ");
    //   Serial.println(vals[i]);
    // }
    } else {
      Serial.print("Расстояние вне допустимого диапазона:");
      Serial.print(min);
      Serial.print(", ");
      Serial.println(max);
    }
  }

  // Задержка между измерениями для корректной работы скеча
  delay(1000);
}

bool check_is_enough() {
  int last_not_zero = 0;
  double count = 0.0;
  for (int i = 0; i < max - min; i++) {
      if (vals[i] != 0) {
        count++;
      } else {
        if (i - last_not_zero >= 2) {
          return false;
        }
        last_not_zero = i;
      }
    }
  return count / (max - min) >= 0.9;
}

void show_bad() {
  digitalWrite(LED_BAD, HIGH);
}

void show_ok() {
  digitalWrite(LED_BAD, LOW);
  digitalWrite(LED_OK, HIGH);
}

void send_mess() {
  Serial.println("message");
  Serial.println(max - min);
  for (int i = 0; i < max - min; i++) {
    String stringValue = String(vals[i], 3);
    Serial.println(stringValue);
    Serial.println(i + min);
  }
}

