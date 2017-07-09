#ifndef MPUX_h
#define MPUX_h

class MPUX {
	private:
		byte error_mpu, address;
		
		int nDevices;
		int MPU;
		unsigned long timeCompute, lastCompute;
		unsigned long realTime, lastTime;
		
		double value, lastValue;		
		double GyX, GyY, GyZ, Tmp, AcX, AcY, AcZ;
		double GyX_End, GyY_End, GyZ_End, Tmp_End, AcX_End, AcY_End, AcZ_End;
		double PID;
		double P, I, D;
		double kP, kI, kD;
		double TargetPoint, error;
		double minRangeOutput, maxRangeOutput;
		
		bool setRange;
		
		double Process(double);
		
	
	public:
		MPUX(int);
		void init();
		void compute();
		double getGyX();
		double getGyY();
		double getGyZ();
		double getTmpCel();
		double getTmpFah();
		double getAcX();
		double getAcY();
		double getAcZ();
		
		double getGyXPID();
		double getGyYPID();
		double getGyZPID();
		double getAcXPID();
		double getAcYPID();
		double getAcZPID();
		
		void setNotRange();
		void setTargetPoint(int);
		void setOutputLimits(double, double);
		void setConstants(double, double, double);
};
#endif

