/**********************************************************************************************
 * Arduino MPU-6050 Library - Version 0.1
 * by Alessandro Vinicius <alessandro.vncs@gmail.com>
 *
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MPUX.h>
#include <Wire.h>


MPUX::MPUX(int address){	
	MPU = address;
	//init();
}

void MPUX::init(){
	Wire.begin();
	Wire.beginTransmission(0x68);
	Wire.write(0x6B); 
	Wire.write(0); 
	Wire.endTransmission(true);
	
	timeCompute = 5;
	lastCompute = 0;
	kP = 0.0056;
	kI = 0.0;
	kD = 0.0;
	TargetPoint = 0.0;
	setRange = false;
	maxRangeOutput = 0;
	minRangeOutput = 0;
}


void MPUX::compute(){
	if(lastCompute <= millis()){
		lastCompute = millis() + timeCompute; 
		Wire.beginTransmission(0x68);
		Wire.write(0x3B);  // starting with register 0x3B (GYRO_XOUT_H)
		Wire.endTransmission(false);
		
		//Solicita os dados do sensor
		Wire.requestFrom(0x68,14,true);  
		
		//Armazena o valor dos sensores nas variaveis correspondentes
		GyX=Wire.read()<<8|Wire.read(); //0x3B (GYRO_XOUT_H) & 0x3C (GYRO_XOUT_L)     
		GyY=Wire.read()<<8|Wire.read(); //0x3D (GYRO_YOUT_H) & 0x3E (GYRO_YOUT_L)
		GyZ=Wire.read()<<8|Wire.read(); //0x3F (GYRO_ZOUT_H) & 0x40 (GYRO_ZOUT_L)
		Tmp=Wire.read()<<8|Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
		AcX=Wire.read()<<8|Wire.read(); //0x43 (ACCEL_XOUT_H) & 0x44 (ACCEL_XOUT_L)
		AcY=Wire.read()<<8|Wire.read(); //0x45 (ACCEL_YOUT_H) & 0x46 (ACCEL_YOUT_L)
		AcZ=Wire.read()<<8|Wire.read(); //0x47 (ACCEL_ZOUT_H) & 0x48 (ACCEL_ZOUT_L)
	}
}

double MPUX::getGyX(){
	return GyX;
}

double MPUX::getGyY(){
	return GyY;
}

double MPUX::getGyZ(){
	return GyZ;
}

double MPUX::getTmpCel(){ 
	Tmp_End = Tmp/340.00+36.53;
	return Tmp_End;
}

double MPUX::getTmpFah(){ //f = 1.8c + 32
	Tmp_End = 1.8 * (Tmp/340.00+36.53) + 32;
	return Tmp_End;
}

double MPUX::getAcX(){
	return AcX;
}

double MPUX::getAcY(){
	return AcY;
}

double MPUX::getAcZ(){
	return AcZ;
}

//Com PID

double MPUX::Process(double value){
	error = TargetPoint - value;
	
	realTime = (millis() - lastTime)/1000.0;
	lastTime = millis();
	
	P = error * kP;
	I += error * kI / realTime;
	D = (lastValue - value) * kD / realTime;
	
	lastValue = value;
	
	PID = P + I + D;
	
	if(PID > maxRangeOutput && setRange){
		PID = maxRangeOutput;
	}else if(PID < minRangeOutput && setRange){
		PID = minRangeOutput;
	}
	
	return PID;
}

void MPUX::setOutputLimits(double Min, double Max){
	minRangeOutput = Min;
	maxRangeOutput = Max;
	setRange = true;
}

void MPUX::setTargetPoint(int new_TargetPoint){
	TargetPoint = new_TargetPoint;
}

void MPUX::setNotRange(){
	setRange = false;
}

void MPUX::setConstants(double _kP, double _kI, double _kD){
	kP = _kP;
	kI = _kI;
	kD = _kD;
}

//fim exec PID

double MPUX::getGyXPID(){
	GyX_End = Process(getGyX());
	return GyX_End;
}

double MPUX::getGyYPID(){
	GyY_End = Process(getGyY());
	return GyY_End;
}

double MPUX::getGyZPID(){
	GyZ_End = Process(getGyZ());
	return GyZ_End;
}

double MPUX::getAcXPID(){
	AcX_End = Process(getAcX());
	return AcX_End;
}

double MPUX::getAcYPID(){
	AcY_End = Process(getAcY());
	return AcY_End;
}

double MPUX::getAcZPID(){
	AcZ_End = Process(getAcZ());
	return AcZ_End;
}