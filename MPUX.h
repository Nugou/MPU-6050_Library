#ifndef MPUX_h
#define MPUX_h

class MPUX {
	private:
		byte error, address;
		
		int nDevices;
		int MPU;
		unsigned long timeCompute, lastCompute;
		unsigned long realTime, lastTimte;
		
		double value, lastValue;		
		double GyX, GyY, GyZ, Tmp, AcX, AcY, AcZ;
		double PID;
		double P, I, D;
		double kP, kI, kD;
		double targertPoint;
		double minRangeOutput, maxRangeOutput;
		
		boolean setRange;
		
		double PID(double);
		
	
	public:
		MPUX();
		void Compute();
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

