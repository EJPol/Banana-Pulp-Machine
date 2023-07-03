#include <Servo.h>
Servo servo;

#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

#define pushbutton1 5
#define pushbutton2 6
#define pushbutton3 7

// DC MOTOR connections
int enA = 2;          
int in1 = 1;
int in2 = 4;

int RPWM=3;
int LPWM=11;
// timer 0
int L_EN=12;
int R_EN=13;

int buttonState1 = 1;
int buttonState2 = 1;
int buttonState3 = 1;

int count1 = 0;
int count2 = 0;

void setup() {
	// Set all the motor control pins to outputs
  lcd.init();                           //initialize the lcd
  lcd.backlight();                      //open the backlight 
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
	
  // Initiate push buttons
  pinMode(pushbutton1, INPUT_PULLUP);
  pinMode(pushbutton2, INPUT_PULLUP);
  pinMode(pushbutton3, INPUT_PULLUP);

  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, LOW);
  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);

  // Initialize serial monitor
  Serial.begin(9600);

  servo.attach(0);

  servo.write(0);
}

void Washing() {
  lcd.clear();
  lcd.setCursor(2, 1);         // move cursor to   (0, 0)
  lcd.print("Washing Mode");

  // Turn on motors
  digitalWrite(R_EN,HIGH);
  digitalWrite(L_EN,HIGH);
    
  // Accelerate from zero to maximum speed
  for (int i = 10; i < 40; i++) {
    analogWrite(RPWM, i);
    delay(300);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 40; i >= 10; --i) {
    analogWrite(RPWM, i);
    delay(300);
  }

  delay(20);

  for (int i = 10; i < 40; i++) {
    analogWrite(LPWM, i);
    delay(200);
  }

  // Accelerate from zero to maximum speed
  for (int i = 40; i >= 10; --i) {
    analogWrite(LPWM, i);
    delay(200);
  }

  for (int i = 10; i < 40; i++) {
    analogWrite(RPWM, i);
    delay(200);
  }
    
  // Decelerate from maximum speed to zero
  for (int i = 40; i >= 10; --i) {
    analogWrite(RPWM, i);
    delay(200);
  }

  delay(20);

  for (int i = 10; i < 40; i++) {
    analogWrite(LPWM, i);
    delay(200);
  }

  // Accelerate from zero to maximum speed
  for (int i = 40; i >= 10; --i) {
    analogWrite(LPWM, i);
    delay(200);
  }
    
}

void Blender() {
  lcd.clear();
  lcd.setCursor(2, 1);         // move cursor to   (0, 0)
  lcd.print("Blending Mode");
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
  digitalWrite(R_EN,HIGH);
  digitalWrite(L_EN,HIGH);
  delay(500);

  while (count1%2 == 0){
    // Turn on motor B
    digitalWrite(R_EN,HIGH);
    digitalWrite(L_EN,HIGH);

    analogWrite(RPWM, 225);

    if (digitalRead(pushbutton2) == LOW){
      for(int i=225; i>0 ; i--) {
        analogWrite(RPWM,i);
        // analogWrite(LPWM,255-i);
        delay(5);
      }
      count1 += 1;
    }
  }
  count1 += 1;

}

void DrainOpen(){
  digitalWrite(enA, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Opening Drain");
  servo.write(90);
  delay(5000);
  count2 += 1;
  digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void DrainClose(){
  digitalWrite(enA, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Closing Drain");
  servo.write(0);
  delay(5000);
  count2 += 1;
  digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}


void loop() {
  buttonState1 = digitalRead(pushbutton1);
  buttonState2 = digitalRead(pushbutton2);
  buttonState3 = digitalRead(pushbutton3);
  
  lcd.clear();                 // clear display
  lcd.setCursor(5, 1);         // move cursor to   (0, 0)
  lcd.print("Pulp Maker");        // print message at (0, 0)
  lcd.setCursor(4, 2);         // move cursor to   (2, 1)
  lcd.print("CHOOSE the Mode");     // print message at (2, 1)
  delay(500);                 // display the above for two seconds

	if (buttonState1 == LOW){
    Serial.println("WASH");
    Washing();
  }
  else if (buttonState2 == LOW){
    Serial.println("BLEND");
    Blender();
  }
  else if (buttonState3 == LOW){
    if (count2%2 == 0){
      Serial.println("OPEN");
      DrainOpen();      
    }
    else{
      Serial.println("CLOSE");
      DrainClose();
    }
  }

	delay(200);
}
