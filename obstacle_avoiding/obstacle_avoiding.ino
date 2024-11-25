#include "SR04.h"
#define TRIG_PIN 10
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;           
#define IN_1  7       
#define IN_2  4        
#define IN_3  3           
#define IN_4  2 

void setup()
{
pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 

Serial.begin(9600);
}
void loop()
{
a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   delay(100);
    // If you dont get proper movements of your robot then alter the pin numbers
  if (a > 15)            
  {
    digitalWrite(IN_1,LOW );
digitalWrite(IN_2, HIGH);
digitalWrite(IN_3, HIGH);
digitalWrite(IN_4, LOW);                                                  
  }

  if (a < 14)
  {
    digitalWrite(IN_1,LOW );
digitalWrite(IN_2, LOW);
digitalWrite(IN_3, LOW);
digitalWrite(IN_4, LOW);
    delay(500);
    digitalWrite(IN_1, HIGH);
digitalWrite(IN_2, LOW);
digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, HIGH);
    delay(500);
    digitalWrite(IN_1,LOW );
digitalWrite(IN_2, LOW);
digitalWrite(IN_3, LOW);
digitalWrite(IN_4, LOW);  
    delay(100);  
    digitalWrite(IN_1,HIGH );
digitalWrite(IN_2, LOW);
digitalWrite(IN_3, LOW);
digitalWrite(IN_4, LOW);
    delay(600);
  }

}
