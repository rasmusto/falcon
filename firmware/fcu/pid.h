volatile struct pidInfo {
	float kp;
	float ki;
	float kd;
	
	float i;
	
	float previousError;  //does this apply to both roll and pitch?
	uint32_t previousTime;
	
	float target;
};

float pidIteration (volatile struct pidInfo* pid, float value, uint32_t timeStamp);
void pidSetKp (volatile struct pidInfo* pid, float kp);
void pidSetKi (volatile struct pidInfo* pid, float ki);
void pidSetKd (volatile struct pidInfo* pid, float kd);
void pidSetTarget (volatile struct pidInfo* pid, float target);
void printPidInfo(volatile struct pidInfo * pid);
void resetI (volatile struct pidInfo* pid);
