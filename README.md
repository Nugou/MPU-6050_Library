# MPU-6050 Library (MPUX)

This library of easy access provides comands to receive all that module MPU-6050 offers.


# Instalacion

To install, download and extract to the folder 'libraries' of arduino(C:\Program Files (x86)\Arduino\libraries\), done; 

# Comands

Instance: MPUX MPU(address); -> Instance with int address of MPU-6050, usually '0x68';

*-> name of reference;

To start library, use comands: 

*.init(); -> This does some parameters to start;  
*.compute(); -> This does MPU-6050 calculate: temperature, parameters of gyroscope and parameters of accelerometers;

	--After '*.compute();', you should take parameters of MPU-6050 like Gyroscope(that think more important);
	
*.getGyX(); -> This return a 'double' with the parameter 'X' of Gyroscope;
*.getGyY(); -> This return a 'double' with the parameter 'Y' of Gyroscope;
*.getGyZ(); -> This return a 'double' with the parameter 'Z' of Gyroscope;

*.getTmpCel(); -> This return a 'double' with the parameter temperature in Celsius of Module;
*.getTmpFah(); -> This return a 'double' with the parameter temperature in Fahrenheit of Module;

*.getAcX(); -> This return a 'double' with the parameter 'X' of Accelerometers;
*.getAcY(); -> This return a 'double' with the parameter 'Y' of Accelerometers;
*.getAcZ(); -> This return a 'double' with the parameter 'Z' of Accelerometers;

# Tips

You can work this library together 'PIDX'. With library 'PIDX' you used the proporcion to get value more clean;

With library PIDX and setting in constans 'kP' a value '0.0056', you will receive value of angle, just in Gyroscope;

To knows the address of MPU-6050, get the code 'I2C Scanner'(I have in my repository too, but isn't my) and install in your arduino, connect the module in arduino and open the Serial Monitor;
 

# Change Log
1.2 - Bugs fixed and PID codes removed; (use the library PIDX);
1.0 - Library finished;
