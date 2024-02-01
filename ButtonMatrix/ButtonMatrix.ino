

int write_pins[2] = {8, 9};
int read_pins[2] = {10, 11};


int states[2][2] = {
  { 0, 0 },
  { 0, 0 }
};

void setup() {
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
}

int values[2] = {0, 0};

int last_states[2][2] = {
  { 0, 1 },
  { 1, 0 }
};

void read_states(int i) {
  states[i][0] = !digitalRead(read_pins[0]);
  states[i][1] = !digitalRead(read_pins[1]);
}

bool to_print() {
  for (int i = 0; i < 2; i ++) {
    for (int j = 0; j < 2; j ++) {
      if (states[i][j] != last_states[i][j]) {
        return true;
      }
    }
  }
  return false;
}

void print_states() {
    for (int i = 0; i < 2; i ++) {
      for (int j = 0; j < 2; j ++) {
        Serial.print(states[i][j]);
        Serial.print(" ");
        last_states[i][j] = states[i][j];
      }
    }
    Serial.println();
}

void loop() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(write_pins[0], i);
    digitalWrite(write_pins[1], (i + 1) % 2);

    read_states(i);

    if (to_print()) {
      print_states();
    }

    delay(5);
  }
  
}
