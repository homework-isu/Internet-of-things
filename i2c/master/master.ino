#include <Wire.h>

#define PHOTO_RES A0
#define SLAVE_ADDRES 9


bool is_calibration = false;
bool is_report_sended = false;
bool data_send_aborted = false;
bool showData = false;
bool min_range_checked = false;
bool max_range_checked = false;
int min_range = -1;
int max_range = -1;

int previous = -1;
int cntr = 0;
int records_to_do = 0;


const int STEP = 10;
const int DIFF = 10;
const int ARCHIVE_FACTOR = 5;

int getMyPhotoResValue(){
  return analogRead(PHOTO_RES);
}

void setup() {
  pinMode(PHOTO_RES, INPUT);
  Serial.begin(9600);
  Serial.println("dungeon master");
  Wire.begin();
}

void switch_show_data() {
    showData = !showData;
}

void loop() {
   if (showData) {
      Serial.print("value: ");
      Serial.println(getMyPhotoResValue());
    }

  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 's') {
      switch_show_data();
    }

    if (cmd == 'c') {
      Serial.println("'o' to confirm. LIGHT OFF");
    }

    if (cmd == 'r'){
      is_calibration = false;
      is_report_sended = false;
      data_send_aborted = false;
      min_range = -1;
      max_range = -1;
      max_range_checked = false;
      min_range_checked = false;
      previous = -1;
      cntr = 0;
      records_to_do=0;
      Serial.println("Resetted");
    }

    if (cmd == 'o') {
      if (min_range == -1) {
        min_range = getMyPhotoResValue() + DIFF;
        Serial.println("'o' to confirm. LIGHT ON");
      } else if (max_range == -1) {
        max_range = getMyPhotoResValue() - DIFF;
        is_calibration = true;

        Wire.beginTransmission(SLAVE_ADDRES);
        Wire.write('r');
        records_to_do  = (int)((max_range - min_range + 1) / STEP);
        Wire.write(records_to_do);
        Serial.print("awaiting records: ");

        Serial.println(records_to_do);


        Wire.endTransmission(SLAVE_ADDRES);
        Serial.println(min_range);
        Serial.println(max_range);
        Serial.println("WATCH OUT!!! DANGEROUS CALLIBRATION");
        delay(5000);
      }
    }
  }
  if (is_calibration) {
    Wire.beginTransmission(SLAVE_ADDRES);
    if (!is_report_sended) {
      Wire.write("c");
      is_report_sended = true;
    }
    if (is_report_sended && !data_send_aborted){
      int res = getMyPhotoResValue();
      if (res <= min_range && !min_range_checked) {
        min_range_checked = true;
      }
      if (res >= min_range && !max_range_checked) {
        max_range_checked = true;
      }


      if (res - previous >= STEP){
        Serial.print("Value for calibration: ");
        Serial.println(getMyPhotoResValue());
        Wire.write((int)(res / ARCHIVE_FACTOR));
        cntr += 1;
        previous = res;
      }
      Wire.endTransmission(SLAVE_ADDRES);

      if (previous == -1){
        previous = res;
      }
    }
    if (min_range_checked && max_range_checked && cntr >= records_to_do ) {
      is_calibration = false;
      is_report_sended = false;
      data_send_aborted = false;

      min_range = -1;
      max_range = -1;

      Wire.beginTransmission(SLAVE_ADDRES);
      Wire.write('s');
      Wire.endTransmission(SLAVE_ADDRES);
      Serial.println("finished... (dies)");
      showData = true;
    }
  }
}