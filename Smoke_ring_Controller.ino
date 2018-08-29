// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Smoke_ring_Controller.ino
    Created:	2018/8/28 11:33:04
    Author:     DeFront\Magnus
*/

#define Trig 2
#define Echo 3
#define dynamic_motor_positive 7
#define dynamic_motor_negative 8
#define blower_motor_positive 11
#define blower_motor_negative 12
#define enb 13
#define ena 9

float cm;
float distance;

// user function
// get data from ultrasonic wave sensor and print
void distanceData()
{
	digitalWrite(Trig, 0);
	delay(2);
	digitalWrite(Trig, 1);
	delay(10);
	digitalWrite(Trig, 0);

	distance = pulseIn(Echo, HIGH) / 58.0;
	Serial.println(distance);
	delay(200);
}

// control blower motor
void blower(bool customer)
{
	digitalWrite(blower_motor_negative, 0);
	digitalWrite(blower_motor_positive, customer);
	analogWrite(enb, 250);
	delay(1000);
	analogWrite(enb, 130);
	delay(10);
}

//  control dynamic motor
void dynamicMotor()
{
	Serial.println("smoke ring out");
	digitalWrite(dynamic_motor_positive, 1);
	digitalWrite(dynamic_motor_negative, 0);
	analogWrite(ena, 255);
	delay(130);
	digitalWrite(dynamic_motor_positive, 0);
	digitalWrite(dynamic_motor_negative, 0);
	delay(100);
	digitalWrite(dynamic_motor_positive, 0);
	digitalWrite(dynamic_motor_negative, 1);
	delay(130);
	digitalWrite(dynamic_motor_positive, 0);
	digitalWrite(dynamic_motor_negative, 0);
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	pinMode(Trig, 1);
	pinMode(Echo, 0);
	pinMode(dynamic_motor_positive, 1);
	pinMode(dynamic_motor_negative, 1);
	pinMode(blower_motor_positive, 1);
	pinMode(blower_motor_negative, 1);
	pinMode(enb, 1);

	digitalWrite(dynamic_motor_positive, 0);
	digitalWrite(dynamic_motor_negative, 0);
	digitalWrite(blower_motor_positive, 0);
	digitalWrite(blower_motor_negative, 0);
}

// Add the main program code into the continuous loop() function
void loop()
{
	distanceData();

	if (distance <= 30)
	{
		blower(1);
		delay(4000);
		dynamicMotor();
		distanceData();
		while (distance <= 30)
		{
			delay(2500);
			dynamicMotor();
			distanceData();
		}
		blower(0);
	}
}
