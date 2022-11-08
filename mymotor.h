constexpr int mot1a = 5;
constexpr int mot1b = 3;
constexpr int mot2a = 6;
constexpr int mot2b = 9;

int speed = 0;

void setupMotor() {
	pinMode(mot1a, OUTPUT);
	pinMode(mot1b, OUTPUT);
	pinMode(mot2a, OUTPUT);
	pinMode(mot2b, OUTPUT);
}

void setSpeed(int s) {
	speed = s;
}

void drive() {

	int m1as = 0, m1bs = 0, m2as = 0, m2bs = 0;

	if (speed < 0) {
		m1as = abs(speed);
		m2as = abs(speed);
	}
	else {
		m1bs = abs(speed);
		m2bs = abs(speed);
	}

	analogWrite(mot1a, m1as);
	analogWrite(mot1b, m1bs);
	analogWrite(mot2a, m2as);
	analogWrite(mot2b, m2bs);
}
