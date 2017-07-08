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


MPUX::MPUX(){	

	MPU = addressMPU();
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0); 
	Wire.endTransmission(true);
	
}

void init(){
	timeCompute = 5;
	kP = 0.0056;
	kI = 0.0;
	kD = 0.0;
	targetPoint = 0.0;
	setRange = false;
}

int addressMPU(){
	Wire.begin();           
     
	nDevices = 0;
	for(address = 1; address < 127; address++ ){
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
        if (error == 0){
			//Serial.print("I2C device encontrado no endereço 0x");
			if (address<16){
				Serial.print("0");
			}
			//Serial.print(address,HEX);
			//Serial.println("  !");
     
			nDevices++;
		}else if (error==4){
			//Serial.print("Erro desconhecido no endereço 0x");
			if (address<16){
				Serial.print("0");
			}
			//Serial.println(address,HEX);
		}    
	}
	if (nDevices == 0){
		//Serial.println("Nenhum I2C encontrado\n");
	}else{
		//Serial.println("Concluido\n");
	}
	return int(address,HEX);
}

boolean MPUX::available(){
	if(nDevices > 0){
		return true;
	}
	return false;
}

void MPUX::Compute(){
	if(lastCompute >= millis()){
		lastCompute = millis() + timeCompute; 
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
		
		TempCel = Tmp/340.00+36.53;
		TempFah = 1.8(Tmp/340.00+36.53) + 32;
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
	return Tmp/340.00+36.53;
}

double MPUX::getTmpFah(){ //f = 1.8c + 32
	return 1.8(Tmp/340.00+36.53) + 32;
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

double MPUX::PID(double value){
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
	return MPUX::PID(MPUX::getGyX());
}

double MPUX::getGyYPID(){
	return MPUX::PID(MPUX::getGyY());
}

double MPUX::getGyZPID(){
	return MPUX::PID(MPUX::getGyZ());
}

double MPUX::getAcXPID(){
	return MPUX::PID(MPUX::getAcX());
}

double MPUX::getAcYPID(){
	return MPUX::PID(MPUX::getAcY());
}

double MPUX::getAcZPID(){
	return MPUX::PID(MPUX::getAcZ());
}