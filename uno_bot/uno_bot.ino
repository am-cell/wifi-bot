//uno sucks
#define ENA   3         // Enable/speed motors Right        GPIO14(D5)
#define ENB   6         // Enable/speed motors Left         GPIO12(D6)
#define IN_1  2        // L298N in1 motors Right           GPIO15(D8)
#define IN_2  4         // L298N in2 motors Right           GPIO13(D7)
#define IN_3  5          // L298N in3 motors Left            GPIO2(D4)
#define IN_4  7         // L298N in4 motors Left            GPIO0(D3)
#define horn 8
int avoider = false;
int follower = false ;
char command;             //String to store app command state.

int speedCar = 1023;         // 400 - 1023.
int speed_Coeff = 3;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(horn, OUTPUT);
  Serial.begin(9600);

 
}
void goAhead() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}
void Horn() {
 
}

void goBack() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goLeft() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void goAheadLeft() {

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBackRight() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft() {

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void stopRobot() {
  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}
void obstacle_avoiding()
{
}
void object_follower()
{
 
  }



void loop() {
 if (Serial.available() > 0) {

    command = Serial.read();
    Serial.print(command);
if (avoider)  {obstacle_avoiding();}  
if (follower) {object_follower();}

  switch (command) {
case 'F':goAhead();break;
case 'B':goBack();break;
case 'R':goLeft();break;
case 'L':goRight();break;
case 'G':goAheadRight();break;
case 'I':goAheadLeft();break;
case 'H':goBackRight();break;
case 'J':goBackLeft();break;
case '2':speedCar = 135;break;
case '3':speedCar = 155;break;
case '4':speedCar = 170;break;
case '5':speedCar = 185;break;
case '6':speedCar = 195;break;
case '7':speedCar = 215;break;
case '8':speedCar = 235;break;
case '9':speedCar = 255;break;
case 'S':stopRobot();break;
case 'a':avoider = true;break;
case 'f':follower = true;break;
case 'h':Horn();break;
  }
 }
}
