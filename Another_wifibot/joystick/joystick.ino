#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<Wire.h>
#include <ESP8266WebServer.h>

const char *ssid = "Wifibot";
const char *password = "tonystark";
int Ax , Ay , horn;


const uint8_t scl = 5;
const uint8_t sda = A0;
const uint8_t i = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(i,INPUT);
   pinMode(scl,INPUT);
   pinMode(sda,INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(9600);
   
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  HTTPClient http;
  Ax=digitalRead(scl);
  Ay=analogRead(sda);
  horn=digitalRead(i);
  Serial.print("Ax="); Serial.println(Ax);
  Serial.print("Ay="); Serial.println(Ay);
 http.begin("http://192.168.4.1/?State=4");
    http.GET();
    http.end();
  if (Ay > 900) {

    http.begin("http://192.168.4.1/?State=F");
    http.GET();
    http.end();
    Serial.println("forward");

  }

  else if (Ay < 400) {

    http.begin("http://192.168.4.1/?State=B");
    http.GET();
    http.end();
    Serial.println("backward");
  }

  else if (Ax == 0) {

    http.begin("http://192.168.4.1/?State=L");
    http.GET();
    http.end();
    Serial.println("left");
  }

 
 else if (horn == 1) {

    http.begin("http://192.168.4.1/?State=P");
    http.GET();
    http.end();
    Serial.println("horn");
  }
  
  else {

    http.begin("http://192.168.4.1/?State=S");
    http.GET();
    http.end();
    Serial.println("stop");
  
  }
  delay(100);
}
