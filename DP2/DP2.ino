#include <Servo.h>
Servo servo;

#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

#define pushbutton1 11
#define pushbutton2 12
#define pushbutton3 13

// DC MOTOR connections
int enB = 3;
int in3 = 5;
int in4 = 4;

int buttonState1 = 1;
int buttonState2 = 1;
int buttonState3 = 1;

int count1 = 0;
int count2 = 0;

void setup() {
	// Set all the motor control pins to outputs
  lcd.init();                           //initialize the lcd
  lcd.backlight();                      //open the backlight 
	pinMode(enB, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  // Initiate push buttons
  pinMode(pushbutton1, INPUT_PULLUP);
  pinMode(pushbutton2, INPUT_PULLUP);
  pinMode(pushbutton3, INPUT_PULLUP);

  // Initialize serial monitor
  Serial.begin(9600);

  servo.attach(2);

  servo.write(0);
}

void Washing() {
  lcd.clear();
  lcd.setCursor(2, 1);         // move cursor to   (0, 0)
  lcd.print("Washing Mode");

  // Turn on motors
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Now change motor directions
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }

  // Now change motor directions
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }

  // Now change motor directions
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }

  // Now change motor directions
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }

  // Now change motor directions
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 200; i++) {
    analogWrite(enB, i);
    delay(50);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 199; i >= 0; --i) {
    analogWrite(enB, i);
    delay(50);
  }
}

void Blender() {
  lcd.clear();
  lcd.setCursor(2, 1);         // move cursor to   (0, 0)
  lcd.print("Blending Mode");
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enB, 255);

  while (count1%2 == 0){
    // Turn on motor B
	  digitalWrite(in3, HIGH);
	  digitalWrite(in4, LOW);   

    if (digitalRead(pushbutton2) == LOW){
      count1 += 1;
    }
  }

	// Turn off motors
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void DrainOpen(){
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Opening Drain");
  servo.write(180);
  delay(5000);
  count2 += 1;
}

void DrainClose(){
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Closing Drain");
  servo.write(0);
  delay(5000);
  count2 += 1;
}


void loop() {
  buttonState1 = digitalRead(pushbutton1);
  buttonState2 = digitalRead(pushbutton2);
  buttonState3 = digitalRead(pushbutton3);
  
  lcd.clear();                 // clear display
  lcd.setCursor(5, 1);         // move cursor to   (0, 0)
  lcd.print("Arduino");        // print message at (0, 0)
  lcd.setCursor(4, 2);         // move cursor to   (2, 1)
  lcd.print("Group 4402");     // print message at (2, 1)
  delay(500);                 // display the above for two seconds

	if (buttonState1 == LOW){
    Washing();
  }
  else if (buttonState2 == LOW){
    Blender();
    delay(5000);
  }
  else if (buttonState3 == LOW){
    if (count2%2 == 0){
      DrainOpen();
    }
    else{
      DrainClose();
    }
  }

	delay(200);
}
