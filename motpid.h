constexpr double multi = 6;

constexpr double kp = 1 * multi ;
constexpr double ki = 0 * multi;
constexpr double kd = 1 * multi;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double setPoint;
double cumError, rateError;

void setupPid() {
	setPoint = 0;   
}
/*
half werkend!!!!
1
1






*/

double pidLoop(double inp) {
	currentTime = millis();                //get current time
    elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
    error = setPoint - inp;                                // determine error
    cumError += error * elapsedTime;                // compute integral
    rateError = (error - lastError)/elapsedTime;   // compute derivative
 
    double out = kp*error + ki*cumError + kd*rateError;                //PID output               
 
    lastError = error;                                //remember current error
    previousTime = currentTime;                        //remember current time
 
    return out;   
}