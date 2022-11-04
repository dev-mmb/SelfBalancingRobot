
#include "accelerometer.h"
#include "mymotor.h"
#include "motpid.h"

void setup() {
  Serial.begin(9600);
  setupAcc();
  setupMotor();
  
  Gyro& gyro = getGyro();
  setupPid();
  setSpeed(255);
}
int minv = -900;
int maxv = 900;

void loop() {
  updateAccGyro();

  Gyro& gyro = getGyro();

  double out = pidLoop(gyro.z);
  
  //Serial.println(gyro.z);
  Serial.println(out);
  out = constrain(out, minv, maxv);
  
  int mapped = map((int)out, minv, maxv, -254, 255); 
  if (mapped > 255) mapped = 255;
  if (mapped < -254) mapped = -254;
  //Serial.println(mapped);
  setSpeed(mapped);
 

  drive();
  delay(1);
}
