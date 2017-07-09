#ifndef MPUX_h
#define MPUX_h

class MPUX {
	private:
		int MPU;
		unsigned long timeCompute, lastCompute;
		
		double value, lastValue;		
		double GyX, GyY, GyZ, Tmp, AcX, AcY, AcZ;
		double GyX_End, GyY_End, GyZ_End, Tmp_End, AcX_End, AcY_End, AcZ_End;
		
	
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
};
#endif

