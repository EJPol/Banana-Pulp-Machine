#include <Servo.h>
Servo servo;

// ---Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// ---Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() {
  // ---put your setup code here, to run once:

  // ---Set all the motor control pins to output
  Serial.begin(9600);
  servo.attach(9);

	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);

	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// ---Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
}

void Blending_Mode() {
  // ---Set motors to maximum speed
	// ---For PWM maximum possible values are 0 to 255
	//analogWrite(enA, 255);
	analogWrite(enB, 255);

	// ---Turn on motor A & B
	//digitalWrite(in1, HIGH);
	//digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  Serial.print("BLENDING MODE: ON");
	delay(3000);
	
	// ---Turn off motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void Washing_Mode() {
  // ---Set motors to maximum speed
	// ---For PWM maximum possible values are 0 to 255
	//analogWrite(enA, 255);
	analogWrite(enB, 35);
	
	// ---Now change motor directions
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(1000);
	
	// ---Turn off motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}
// ----This function lets you control speed of the motors
void Blending_Speed() {
	// ---Turn on motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);

  Serial.print("BLENDING SPEED: ON");
	
	// ---Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		//analogWrite(enA, i);
		analogWrite(enB, i);
    Serial.print("BS:");
    Serial.println(i);
    //if (i = 255) {
     // delay(10000);
     // Serial.print("BS MAX!!!");
    //}
		delay(20);
	}
	
	// ---Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		//analogWrite(enA, i);
		analogWrite(enB, i);
    //if (i = 255) {
      //delay(10000);
    //}
		delay(20);
	}
	
	// ---Now turn off motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void Washing_Speed() {
	// ---Turn on motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// ---Accelerate from zero to maximum speed
	for (int i = 0; i < 36; i++) {
		//analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// ---Decelerate from maximum speed to zero
	for (int i = 35; i >= 0; --i) {
		//analogWrite(enA, i);
		analogWrite(enB, i);
    delay(20);
	}
	
	// ---Now turn off motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void Drain_Open() {
  // ---Set motors to maximum speed
	// ---For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);

	// ---Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  servo.write(90);    // Move the servo to the 90-degree position
  delay(5000);       // Wait for 5 seconds

}

void Drain_Close() {
  // ---Set motors to maximum speed
	// ---For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);

	// ---Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  servo.write(0);    // Move the servo to the 90-degree position
  delay(5000);       // Wait for 5 seconds

}

void loop() {
  // ---put your main code here, to run repeatedly:
  Blending_Mode();
	delay(1000);
	Blending_Speed();
	delay(1000);
  Washing_Mode();
	delay(1000);
	Washing_Speed();
  delay(1000);
  Drain_Open();
  delay(3000);
  Drain_Close();
  delay(3000);

}


