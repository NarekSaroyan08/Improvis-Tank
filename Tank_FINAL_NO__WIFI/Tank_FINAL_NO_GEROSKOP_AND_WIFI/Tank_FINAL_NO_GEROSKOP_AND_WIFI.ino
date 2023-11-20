#include <Servo.h>
#include<Wire.h>

const int MPU_addr=0x68; 

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

Servo servoX;
Servo servoY;
Servo servoZ;

int xCoordinate = 0;
int yCoordinate = 0;
int readyToRotateZ = 0;
int shoot_CNT = 1;
void setup() {

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  servoX.attach(6);
  servoY.attach(5);
  servoZ.attach(7);
  servoX.write(90);
  servoY.write(0);
  servoZ.write(90);

}


void loop() {
  Serial.println("Enter X coordinate:");
  while (Serial.available() == 0);
  {
    xCoordinate = Serial.parseInt();
    Serial.println("X coordinate received: " + String(xCoordinate));
    servoX.write(xCoordinate);
  }
  Serial.println("Enter Y coordinate:");
  while (Serial.available() == 0);
  {
    yCoordinate = Serial.parseInt();
    Serial.println("Y coordinate received: " + String(yCoordinate));
    servoY.write(yCoordinate);
  }
  // Serial.println("Enter how many bullets to shoot");

  Serial.println("Ready to rotate Z? Enter 1 if yes: ");
  while (Serial.available() == 0);
  {
    readyToRotateZ = Serial.parseInt();
  }
  if (readyToRotateZ == 1) 
  {
    servoZ.write(5);
    delay(1500 * shoot_CNT);
    servoZ.write(90);
  }

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);

  delay(1000);
}
