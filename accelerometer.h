#include "Wire.h"
#include <SimpleKalmanFilter.h>

constexpr int MPU_ADDR = 0x68; 
SimpleKalmanFilter xf(2, 2, 0.01);
SimpleKalmanFilter yf(2, 2, 0.01);
SimpleKalmanFilter zf(2, 2, 0.01);


struct Gyro {
	double x, y, z; 
} gyro;

struct Acc {
	double x, // roll
	y, // yaw
	z; // pitch
} acc;

char tmp_str[7];


inline int32_t getZero() {
	return 0;
}


char* convert_int16_to_str(int16_t i) { 
	sprintf(tmp_str, "%6d", i);
	return tmp_str;
}

inline void updateAccGyro() {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(0x3B); 
	Wire.endTransmission(false); 
	Wire.requestFrom(MPU_ADDR, 7*2, true);

	int16_t x = Wire.read()<<8 | Wire.read(); 
	int16_t y = Wire.read()<<8 | Wire.read();
	int16_t z = Wire.read()<<8 | Wire.read(); 

	gyro.x = xf.updateEstimate((int)x - getZero()) ;
	gyro.y = yf.updateEstimate((int)y - getZero()) ;
	gyro.z = zf.updateEstimate((int)z - getZero()) ;
	
	int _ = Wire.read()<<8 | Wire.read(); 

	x = Wire.read()<<8 | Wire.read(); 
	y = Wire.read()<<8 | Wire.read(); 
	z = Wire.read()<<8 | Wire.read(); 

	acc.x = (double)x;
	acc.y = (double)y;
	acc.z = (double)z;
}
void setupAcc() {
	Wire.begin();
	Wire.beginTransmission(MPU_ADDR); 
	Wire.write(0x6B); 
	Wire.write(0); 
	Wire.endTransmission(true);

}
inline Gyro& getGyro() {
	return gyro;
}
inline Acc& getAcc() {
	return acc;
}