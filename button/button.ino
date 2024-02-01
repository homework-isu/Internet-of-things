#define BUTTON_PIN 2
#define LED_PIN 3
#define PRESSED HIGH
#define LONG_BOUNCE_TIME 1000
#define SHORT_BOUNCE_TIME 500
#define LED_TIME 1000
#define TIME_TO_ANALIZE 230


int previous_state = 0;
int led_state = 1;
int led_case = 0;
int clicks = 0;
int first_click_time = 0;

long int press_time = 0;
long int release_time = 0;
long int led_light_time = 0;
bool check_button = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, led_state);
}

void loop() {
  int val = digitalRead(BUTTON_PIN);
  if (val == PRESSED and
      previous_state != PRESSED) {
        press_time = millis();
  }
  if (val == !PRESSED and
      previous_state == PRESSED) {
        release_time = millis();
        check_button = true;
  }
  previous_state = val;

  if (check_button) {
    check_button = false;
    if (release_time - press_time > LONG_BOUNCE_TIME) {
      Serial.println("long pressed");
      led_case = 2;
    } else if (release_time - press_time < SHORT_BOUNCE_TIME) {
      Serial.println ("click");
      if (first_click_time == 0 or clicks == 0) {
        clicks = 1;
        first_click_time = millis();
      } else if (millis() - first_click_time < TIME_TO_ANALIZE) {
        clicks++;
      }
    } else {
      Serial.println("unknown");
    }
  }
  if (first_click_time != 0 and clicks != 0) {
    if (millis() - first_click_time >= TIME_TO_ANALIZE ) {
      Serial.println(millis() - first_click_time);
      Serial.print(clicks);
      Serial.println(" short pressed");
      switch (clicks) {
        case 1:
          led_case = 1;
          break;
        case 2:
          led_case = 3;
      }
      first_click_time = 0;
      Serial.println("here");
      clicks = 0;
    }
  }
  
  switch (led_case) {
    case 1:
      digitalWrite(LED_PIN, LOW);
      first_click_time = 0;
      led_case = 0;
    case 2:
      if (led_state == 0) {
        if (led_light_time == 0) {
          led_light_time = millis();
        }
        if (millis() - led_light_time > LED_TIME / 2) {
            led_light_time = millis();
            digitalWrite(LED_PIN, LOW);
            led_state = 1;
          }
      }
      break;
    case 3:
      digitalWrite(LED_PIN, LOW);
  }

  if (led_case != 3) {
    if (millis() - led_light_time > LED_TIME) {
      led_light_time = millis();
      digitalWrite(LED_PIN, HIGH);
      led_state = 0;
    }
  }
}
