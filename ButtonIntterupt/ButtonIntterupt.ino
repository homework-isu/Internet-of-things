#define BUTTON_PIN 2
#define BOUNCE_TIME 50
#define PRESSED LOW

volatile bool check_button = false;
int pressed_count = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(0, process_button_click, FALLING);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 3125;
  TCCR1B |= (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS12); 
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  if(check_button == true and digitalRead(BUTTON_PIN) == PRESSED) {
      pressed_count++;
      check_button = false;
  }
}

void loop() {
  delay(2000);
  if (pressed_count){
    Serial.print("Pressed: ");
    Serial.println(pressed_count);
    pressed_count=0;
  }
  
}

void process_button_click() {
  if (check_button == false) {
    check_button = true;
  }
}