#include <Wire.h>
#include <MPU6050.h>
#include <SimpleKalmanFilter.h>
MPU6050 mpu;
SimpleKalmanFilter zf(2, 2, 0.01);
int roll = 0;

inline int32_t getZero() {
	return 96;
}

inline void updateAccGyro() {
	// Read normalized values 
	Vector normAccel = mpu.readNormalizeAccel();

	int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
	roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

}
void setupAcc() {
	while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
	{
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		delay(500);
  	}                      //end the transmission
}
inline float getGyro() {
	return roll;
}
