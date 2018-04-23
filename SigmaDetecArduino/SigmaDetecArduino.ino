// Arduino/Teensy example for Arduino Braccio
#undef PI
#undef HALF_PI
// Include the library InverseK.h
#include <Servo.h>
#include <Braccio.h>
#include <InverseK.h>

// docs on braccio
// 670 is length of braccio



Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
	// Setup the lengths and rotation limits for each link
	Link baseh, upperarmh, forearmh, handh;
	Braccio.begin();
	
	baseh.init(0, b2a(0.0), b2a(180.0));
	upperarmh.init(200, b2a(15.0), b2a(165.0));
	forearmh.init(200, b2a(0.0), b2a(180.0));
	handh.init(270, b2a(0.0), b2a(180.0));
	
	// Attach the links to the inverse kinematic model
	InverseK.attach(baseh, upperarmh, forearmh, handh);

}
float a0, a1, a2, a3, mouth;
void loop() {
	//raccio.ServoMovement(30, 90, 90, 90, 90, 90, 90);
	String Input="";
	float coords[3];
	for(int i =0; i<3; i++)
	{
		while (Input.toFloat() == 0) 
		{
			Input = Serial.readString();
			if (Input == "open") {
				mouth = 10;
				Braccio.ServoMovement(30, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, mouth);
			}
			else if (Input == "close") {
				mouth = 38;
				Braccio.ServoMovement(30, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, mouth);
			}
		}
		coords[i] = Input.toFloat();
		Serial.print("coord ");
		Serial.println(coords[i]);
		while (Input != ";") {
			Input = Serial.readString();
		}
		

		
	}
	
	if (!InverseK.solve(coords[0], coords[1], coords[2], a0, a1, a2, a3,0)) {
		Serial.println("failed");
	}
	else {
		Braccio.ServoMovement(30, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, mouth);
		Serial.println("moving");
	}
}

// Quick conversion from the Braccio angle system to radians 
float b2a(float b) {
	return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
	return (a + HALF_PI) * 180 / PI;
}