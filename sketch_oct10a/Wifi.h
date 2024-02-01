#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WiFiMulti.h"


ESP8266WiFiMulti wiFiMulti;
WiFiClient wiFiClient;

String ip = "IP not set";

String id() {
  int mac_len = WL_MAC_ADDR_LENGTH;
  uint8_t mac[mac_len];
  WiFi.softAPmacAddress(mac);
  String mac_id = String(mac[mac_len - 2], HEX) + String(mac[mac_len - 1], HEX);

  return mac_id;
}

bool start_AP_mode() {
  IPAddress ap_IP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ap_IP, ap_IP, IPAddress(255, 255, 255, 0));
  WiFi.softAP((AP_NAME + id()).c_str(), AP_PASSWORD.c_str());
  Serial.println("WiFI started in AP mode " + AP_NAME + " " + id());

  return true;
}

bool start_client_mode(String ssid, String pass) {
  wiFiMulti.addAP(ssid.c_str(), pass.c_str());
  while(wiFiMulti.run() != WL_CONNECTED) {
    delay(10);
  }
  return true;
}

bool init_WIFI(bool AP_mode) {
  ip = WiFi.softAPIP().toString();

  if (AP_mode) {
    start_AP_mode();
    ip = WiFi.softAPIP().toString();
  } else {
    start_client_mode(AP_NAME, AP_PASSWORD);
    ip = WiFi.localIP().toString();
  }
  Serial.println("IP address: " + ip);
  return true;
}
