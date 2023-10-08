int led_pin = 13;
void setup() {
	pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {	
	if (Serial.available() > 0) {
		char cmd = Serial.read();
		if (cmd == 'u') {// u for up/on digitalWrite(led_pin, HIGH); // use LOW or Serial.print("led on");
			digitalWrite(led_pin, HIGH);
			Serial.println("led on");
		} 
		if (cmd == 'd') { // d for down/off digitalWrite(led_pin, LOW); Serial.print("led off");
			digitalWrite(led_pin, LOW);
			Serial.println("led off");
		}
	}
}