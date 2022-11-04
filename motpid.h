double kp = 0.07;
double ki = 0;
double kd = 1;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;


void setupPid() {
	setPoint = 0;   
}

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