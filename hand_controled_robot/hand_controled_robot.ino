
#define IN_1  16         
#define IN_2  5         
#define IN_3  4           
#define IN_4  14         

#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>
IPAddress ip(192,168,4,1);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,4,1);

String command;             //String to store app command state.
      // 400 - 1023.


const char* ssid = "Jarvis";
const char* password = "tonystark";
ESP8266WebServer server(80);

void setup() {
 

 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(9600);
  
// Connecting WiFi

  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(ssid, password);
server.on("/",handleRoot);
 server.on("/S",stopRobot);
 server.on("/F",goAhead);
 server.on("/B",goBack);
 server.on("/L",goLeft);
 server.on("/R",goRight);
 server.begin();
  
 
    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
     

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4,LOW);
      Serial.println("forward");
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2,LOW);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
     Serial.println("backward");
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      Serial.println("right");
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      Serial.println("left");
  }



void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
     Serial.println("stop");
 }

void loop() {
    server.handleClient();
    
     
     
}

void handleRoot(){
  server.send(200,"text/html","Welcome To ErodeRTP");
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW); //RIGHT MOTOR
  
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW); //LEFT MOTOR
}
