//add libraries for stepper motor and lcd display
#include <AccelStepper.h>
#include <LiquidCrystal.h>

//define steper motor parameters
#define STEPS 2048
#define motorPin1 6
#define motorPin2 7
#define motorPin3 8
#define motorPin4 9
#define motorInterfaceType 4 //motor interface- 4 for full step, 8 for half step

//initilize stepper
AccelStepper stepper = AccelStepper(motorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

//initilize lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//global variables
boolean turn = true;
int count = 0;
int number = 1;
int led1;
int led2;
int led3;


void setup() {
  //start serial monitor
  Serial.begin(2000000);
  
  //set max speed for motor
  stepper.setMaxSpeed(1000);
  
  //set up lcd
  lcd.begin(16, 2);
  lcd.print("DEGREES: ");
  lcd.setCursor(0,1);
  lcd.print("Rotation: ");
}

//int turnOnLED(int numb) {
//  if (numb == 1) {
//    //digitalWrite(7, HIGH);
//  }
//  else if (numb == 2) {
//    //digitalWrite(2, HIGH);
//  }
//  else if (numb == 3) {
//    //digitalWrite(3, HIGH);
//  }
//}

void loop() {
  stepper.setCurrentPosition(0);//set stepper position to zero
  stepper.setSpeed(500);//set speed of motor in steps per second
  
  if (count < 3) {//if less than 3 turns
    while (stepper.currentPosition() != 2048) {//while 1 turn not complete (1 turn=2048 steps)
      stepper.runSpeed();//run at specific speed
      Serial.println((stepper.currentPosition()*.1758));//print current position to serial monitor
      int position = stepper.currentPosition()*.1758;//steps into degrees *.1758
      if(position%30==0){//if position is a multiple of 30 degrees print the position
        lcd.setCursor(8,0);
        lcd.print(position);
        lcd.print("   "); 
      }
    }

    //turnOnLED(number);//turn on led 1,2,3 based on what loop you are in
    count++;//add 1 to count
    lcd.setCursor(10,1);
    lcd.print(count);//print the count of turns
    lcd.setCursor(11,1);
    lcd.print("/3"); 
    number++; //add one to the led variable passed to turnOnLED
  }
}
