#include "accelerometer.h"
#include "mymotor.h"
#include "motpid.h"

void setup() {
  Serial.begin(9600);
  setupAcc();
  setupMotor();
  
  float gyro = getGyro();
  setupPid();
  setSpeed(255);
}
constexpr int minv = -200;
constexpr int maxv = 200;

void loop() {
  
  updateAccGyro();

  float gyro = getGyro() + getZero();
  
  double out = pidLoop(gyro);
  
  int mapped = map(out, minv, maxv, -254, 255); 
  Serial.println(out);
//  int deadzone = 30;
//  if (mapped > 0) mapped += deadzone;
//  else if (mapped < 0) mapped -= deadzone;
  
  if (mapped > 255) mapped = 255;
  else if (mapped < -254) mapped = -254;
  //Serial.println(mapped);
  
  setSpeed(mapped);

  drive();
}
