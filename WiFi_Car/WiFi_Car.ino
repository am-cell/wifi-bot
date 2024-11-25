#include "SR04.h"
#define TRIG_PIN 13
#define ECHO_PIN 16
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;
#define IN_1  14
#define IN_2  12
#define IN_3  5
#define IN_4  4
#define buzzer 15

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
// 400 - 1023.


const char* ssid = "Wifibot";
const char* password = "tonystark";
ESP8266WebServer server(80);

void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  Serial.begin(9600);

  // Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();
}

void goAhead() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);


  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

}

void goBack() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

}

void goRight() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);


  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

}

void goLeft() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

}

void goAheadRight() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

}

void goAheadLeft() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

}

void goBackRight() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
}

void goBackLeft() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

}

void stopRobot() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);


  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

}
void obstacle_avoiding()
{
  a = sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  delay(100);
  // If you dont get proper movements of your robot then alter the pin numbers
  if (a > 10)
  {
    digitalWrite(IN_1, LOW );
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
  }

  if (a < 10)
  {
    digitalWrite(IN_1, LOW );
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    delay(500);
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    delay(500);
    digitalWrite(IN_1, LOW );
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    delay(100);
    digitalWrite(IN_1, HIGH );
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    delay(600);
  }

}
void object_follower()
{
  a = sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  delay(100);
  if (a >= 5)
  {
    digitalWrite(IN_1, LOW );
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
  }
  else

  {
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);

  }

}
void horn()
{ digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}
void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "S") stopRobot();
  else if (command == "avoider") obstacle_avoiding();
  else if (command == "follower") object_follower();
  else if (command == "horn") horn();

}

void HTTP_handleRoot(void) {

  if ( server.hasArg("State") ) {
    Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
