   #include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 13
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;           
#define IN_1  16         
#define IN_2  5         
#define IN_3  4           
#define IN_4  14       

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
if(a>=10)
{
digitalWrite(IN_1,LOW );
digitalWrite(IN_2, HIGH);
digitalWrite(IN_3, HIGH);
digitalWrite(IN_4, LOW);
  }
else

{
digitalWrite(IN_1, HIGH);
digitalWrite(IN_2, LOW);
digitalWrite(IN_3, LOW);
 digitalWrite(IN_4, HIGH);
      
  }

}
