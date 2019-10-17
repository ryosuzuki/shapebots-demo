#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUDP.h>

WiFiUDP UDP;
const char *ssid = "Ryo Suzuki";
const char *password = "ryotomomi";
int localPort = 893;

IPAddress HOST_IP(192, 168, 4, 1);
IPAddress myIP(192, 168, 4, 2);

int forward = 12; // D6
int backward = 5; // D1
int left  = 14; // D5
int right = 4; // D2

int extend = 13; // D7 
int retract = 2; // D4

void setup() {
  pinMode(forward, INPUT_PULLUP);
  pinMode(backward, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);  
  pinMode(right, INPUT_PULLUP);

  pinMode(extend, INPUT_PULLUP);
  pinMode(retract, INPUT_PULLUP);
  
  Serial.begin(9600);
  delay(10);

  WiFi.mode(WIFI_STA);
  UDP.begin(localPort);
  connectWiFi();
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  WiFi.config(myIP, WiFi.gatewayIP(), WiFi.subnetMask());

  Serial.println("Start connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void sendWiFi(char byteData[]) {
  if (UDP.beginPacket(HOST_IP, localPort)) {
    UDP.write(byteData);
    UDP.endPacket();
    Serial.println(byteData);
  } else {
    Serial.println("error");
  }
}

void loop() {
  char b[6];
  b[0] = (digitalRead(forward)) ? '1' : '0';
  b[1] = (digitalRead(backward)) ? '1' : '0';
  b[2] = (digitalRead(left)) ? '1' : '0';
  b[3] = (digitalRead(right)) ? '1' : '0';
  b[4] = (digitalRead(extend)) ? '1' : '0';
  b[5] = (digitalRead(retract)) ? '1' : '0';
  sendWiFi(b);
  delay(20);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    Serial.println("disconnect");
    connectWiFi();
  }
}
