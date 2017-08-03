/**********************************************************************************************
 * Arduino MPU-6050 Library - Version 1.2
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
}

void MPUX::init(){
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B); 
	Wire.write(0); 
	Wire.endTransmission(true);
	
	timeCompute = 5;
	lastCompute = 0;
}


void MPUX::compute(){
	if(lastCompute <= millis()){
		lastCompute += timeCompute; 
		Wire.beginTransmission(MPU);
		Wire.write(0x3B);  // starting with register 0x3B (GYRO_XOUT_H)
		Wire.endTransmission(false);
		
		//Solicita os dados do sensor
		Wire.requestFrom(MPU,14,true);  
		
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
