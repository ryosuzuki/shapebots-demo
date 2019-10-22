#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUDP.h>

char WiFibuff[6];
WiFiUDP UDP;
IPAddress myIP;
//IPAddress myIP(192, 168, 4, 1);
const char *ssid = "Ryo Suzuki";
const char *password = "ryotomomi";
int localPort = 893;

int a1 = 0;  // D3
int a2 = 2;  // D4
int b1 = 13; // D7
int b2 = 15; // D8

int c1 = 16; // D0
int c2 = 14; // D5
int d1 = 5;  // D1
int d2 = 4;  // D2

int s1 = 12; // D6
int s2 = A0; // A0

int speed = 300;
int maxLength = 1000;

int currentPos = 0;


void setup() {
  pinMode (a1, OUTPUT);
  pinMode (a2, OUTPUT);
  pinMode (b1, OUTPUT);
  pinMode (b2, OUTPUT);

  pinMode (c1, OUTPUT);
  pinMode (c2, OUTPUT);
  pinMode (d1, OUTPUT);
  pinMode (d2, OUTPUT);

  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);

  Serial.begin(9600);

//  WiFi.mode(WIFI_AP);
//  WiFi.softAP(ssid, password);
//  WiFi.config(myIP, WiFi.gatewayIP(), WiFi.subnetMask());
//  UDP.begin(localPort);

  Serial.println("UDP start");

  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  myIP = WiFi.localIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  UDP.begin(localPort);
  off();

}

void receiveWiFi() {
  UDP.read(WiFibuff, 8);
  Serial.println(WiFibuff);
  UDP.flush();
}

int dir = 0;

void loop() {
//  Serial.println(digitalRead(s1));
//  Serial.println(map(analogRead(s2), 0, 1023, 0, 1));

  if (UDP.parsePacket() > 0) {
    receiveWiFi();

    if(WiFibuff[0] == '0') {
      analogWrite(a1, 0);
      analogWrite(a2, speed);
      analogWrite(b1, speed);
      analogWrite(b2, 0);
      Serial.println("forward");
    } else if(WiFibuff[1] == '0') {
      analogWrite(a1, speed);
      analogWrite(a2, 0);
      analogWrite(b1, 0);
      analogWrite(b2, speed);
      Serial.println("backward");
    } else if(WiFibuff[2] == '0') {
      analogWrite(a1, speed-150);
      analogWrite(a2, 0);
      analogWrite(b1, speed-150);
      analogWrite(b2, 0);
      Serial.println("left");
    } else if(WiFibuff[3] == '0') {
      analogWrite(a1, 0);
      analogWrite(a2, speed-150);
      analogWrite(b1, 0);
      analogWrite(b2, speed-150);
      Serial.println("right");
    } else {
      analogWrite(a1, 0);
      analogWrite(a2, 0);
      analogWrite(b1, 0);
      analogWrite(b2, 0);
      // none
    }

    if(WiFibuff[4] == '0') {
      dir = 1;
    } else if(WiFibuff[5] == '0') {
      dir = -1;
    } else {
      dir = 0;
      stop(1);
      stop(2);      
    }

    if (WiFibuff[6] == '0') {
       initialize(1);
    }
    if (WiFibuff[7] == '0') {
       initialize(2);      
    }
  }

  if (dir > 0) {
    if (currentPos >= maxLength) {
      stop(1);
      stop(2);
    } else {
      up(1);
      up(2);
      currentPos = currentPos + 1;
    }
    Serial.println(currentPos);    
  }
  if (dir < 0) {
    if (digitalRead(s1) == 0) {
      stop(1);
    } else {
      down(1);
    }
    if (map(analogRead(s2), 0, 1023, 0, 1) == 0) {
      currentPos = 0;
      stop(2);
    } else {
      down(2);
      currentPos = currentPos - 1;      
    }  
    Serial.println(currentPos);    
  }  
}


void off() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);

  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
}

void initialize(int num) {
  while (true) {
    down(num);
    delay(1);
    if (digitalRead(s1) == 0) {
      currentPos = 0;
      off();
      break;
    }
    if (map(analogRead(s2), 0, 1023, 0, 1) == 0) {
      currentPos = 0;
      off();
      break;
    }
  }
}

void up(int num) {
  if (num == 1) {
    digitalWrite(c1, LOW);
    digitalWrite(c2, HIGH);
  } else {
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
  }
}

void down(int num) {
  if (num == 1) {
    digitalWrite(c1, HIGH);
    digitalWrite(c2, LOW);
  } else {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
  }
}

void stop(int num) {
  if (num == 1) {
    digitalWrite(c1, LOW);
    digitalWrite(c2, LOW);
  } else {
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
  }
}

void pause(int num) {
  if (num == 1) {
    digitalWrite(c1, HIGH);
    digitalWrite(c2, HIGH);
  } else {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
  }
}
