//Program : Test MPU-6050

#include <MPUX.h> //Include the library of MPU-6050

int address = 0x68; //Address of Sensor

MPUX MYMPU(address); //Instance the library

void setup(){
	Serial.begin(9600);
	MYMPU.init(); //Start parameter of Sensor and library
	Serial.print("Starting...");
}

void loop(){
	MPU.compute(); //Update data of Sensor
	//Show data in Serial Monitor
	Serial.print("Acc. X = "); Serial.print(MYMPU.getAcX()); //Return position X of Accelerometer
	Serial.print(" | Y = "); Serial.print(MYMPU.getAcY()); //Return position Y of Accelerometer
	Serial.print(" | Z = "); Serial.print(MYMPU.getAcZ()); //Return position Z of Accelerometer
	Serial.print(" | Gir. X = "); Serial.print(MYMPU.getGyX()); //Return position X of Gyroscope
	Serial.print(" | Y = "); Serial.print(MYMPU.getGyY()); //Return position Y of Gyroscope
	Serial.print(" | Z = "); Serial.print(MYMPU.getGyZ()); //Return position Z of Gyroscope
	Serial.print(" | Temp = "); Serial.print(MYMPU.getTmpCel()); //Return tempeture in Celsius
	//Serial.print(" | Temp = "); Serial.print(MYMPU.getTmpFah()); //Return tempeture in Fahrenheit
	Serial.println();
}

