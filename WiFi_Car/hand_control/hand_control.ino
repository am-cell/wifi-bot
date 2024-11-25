#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<Wire.h>

const char *ssid = "Jarvis";
const char *password = "";

const uint8_t MPU6050Address = 0x68;

const uint8_t scl = 5;
const uint8_t sda = 4;

const uint16_t AccelScale = 16384;

const uint8_t SMPRT_DIV         = 0x19;
const uint8_t CONFIG            = 0x1A;
const uint8_t GYRO_CONFIG       = 0x1B;
const uint8_t ACCEL_CONFIG      = 0x1C;
const uint8_t FIFO_EN           = 0x23;
const uint8_t INT_ENABLE        = 0x38;
const uint8_t SIGNAL_PATH_RESET = 0x68;
const uint8_t USER_CTRL         = 0x6A;
const uint8_t PWR_MGMT_1        = 0x6B;
const uint8_t PWR_MGMT_2        = 0x6C;

const uint8_t ACCEL_XOUT_H      = 0x3B;

int16_t AccelX, AccelY;

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void I2C_Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, (uint8_t)4);

  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
}

void MPU6050_Init(){
  I2C_Write(MPU6050Address, SMPRT_DIV, 0x07);
  I2C_Write(MPU6050Address, CONFIG, 0x00);
  I2C_Write(MPU6050Address, GYRO_CONFIG, 0x00);
  I2C_Write(MPU6050Address, ACCEL_CONFIG, 0x00);
  I2C_Write(MPU6050Address, FIFO_EN, 0x00);
  I2C_Write(MPU6050Address, INT_ENABLE, 0x00);
  I2C_Write(MPU6050Address, SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050Address, USER_CTRL, 0x00);
  I2C_Write(MPU6050Address, PWR_MGMT_1, 0x00);
  I2C_Write(MPU6050Address, PWR_MGMT_2, 0x00);
}

void setup() {
  // put your setup code here, to run once:
  
  Wire.begin(sda,scl);
  MPU6050_Init();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;
  double Ax, Ay;
  I2C_Read_RawValue(MPU6050Address, ACCEL_XOUT_H);

  Ax=(double)AccelX/AccelScale;
  Ay=(double)AccelY/AccelScale;
Serial.print("Ax=");Serial.println(Ax);
Serial.print("Ay=");Serial.println(Ay);
  if(Ay > 0.3){
    
    http.begin("http://192.168.4.1/F");
    http.GET();
    http.end();
Serial.println("forward");
   
  }

  else if(Ay < -0.3){
    
    http.begin("http://192.168.4.1/B");
    http.GET();
    http.end();
  Serial.println("backward"); 
  }

  else if(Ax < -0.3){
    
    http.begin("http://192.168.4.1/L");
    http.GET();
    http.end();
   Serial.println("left"); 
  }

  else if(Ax > 0.3){
   
    http.begin("http://192.168.4.1/R");
    http.GET();
    http.end();
    Serial.println("right");
  }

  else{
   
    http.begin("http://192.168.4.1/S");
    http.GET();
    http.end();
    Serial.println("stop");
  }
  delay(1);
}
