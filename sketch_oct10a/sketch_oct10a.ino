#include "Config.h"
#include "Wifi.h"
#include "Server.h"
#include "Mqtt.h"


void setup() {
  Serial.begin(9600);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  start_AP_mode();
  // bool wifi_is_on = init_WIFI(True);
  if (wifi_is_on) {
    server_init();
  } else {
    Serial.println("not working");
  }                         
  
  String topic = "esp8266_Danila/command";
  String state_topic = "esp8266_Danila/state";
  mqtt_client.subscribe(topic.c_str());
  mqtt_client.publish(state_topic.c_str(), "hello");
  Serial.println("See me at " + state_topic);
}

void loop() {
  server.handleClient();
  mqtt_client.loop();
}
