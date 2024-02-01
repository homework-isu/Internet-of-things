#include <PubSubClient.h>

PubSubClient mqtt_client(wiFiClient);

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("There is message on topic ");
  Serial.print(topic);
  Serial.print(" Message is: ");
  for (int i = 0; i < length; i++) {
    Serial.print( (char) payload[i]);
  }
  Serial.println("");
}

bool init_MQTT() {
  mqtt_client.setServer(mqtt_broker, mqtt_port); // connect to broker
  mqtt_client.setCallback(callback);
  while (!mqtt_client.connected()) {
    String client_id = "esp8266_" + id();
    if (mqtt_client.connect(client_id.c_str())) {
      Serial.println("MQTT client connected with id: " + client_id);
    } else {
      Serial.println("MQTT client failed to connect");
      delay(500);
    }
  }

  return true;
}