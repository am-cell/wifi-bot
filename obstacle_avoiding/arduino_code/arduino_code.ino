#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// L298N Control Pins
const int LeftMotorForward = 2;
const int LeftMotorBackward = 4;
const int RightMotorForward = 5;
const int RightMotorBackward = 7;
#define ENA   3         // Enable/speed motors Right        GPIO14(D5)
#define ENB   6        // Enable/speed motors Left         GPIO12(D6)
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.

Servo servo_motor;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean goesForward = false;
int distance = 100;
int speedCar = 190;    
void setup()
{
  // Set L298N Control Pins as Output
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
   pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo_motor.attach(9);   // Attachs the servo on pin 9 to servo object.
  servo_motor.write(125);   // Set at 115 degrees. 
  delay(2000);              // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20)
  {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft)
    {
      turnRight();
      delay(300);
      moveStop();
    }
    else
    {
      turnLeft();
      delay(300);
      moveStop();
    }
  
  }
  else
  {
    moveForward(); 
  }

    distance = readPing();
}

int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop()       // Move Stop Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void moveForward()    // Move Forward Function for Motor Driver.
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}
