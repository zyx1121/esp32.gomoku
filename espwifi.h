#ifndef ESPWIFI_H_
#define ESPWIFI_H_
#include <WiFi.h>

const char* ssid = "wifi";
const char* password = "00000000";

void SetupWiFi(void) {
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) delay(500);
}

#endif
