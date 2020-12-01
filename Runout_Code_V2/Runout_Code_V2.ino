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

//initilize LED, will blink when ready and stay solid when running
#define runningLED 13
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

//initilize GO button (this will be used instead of the reset button, reset will be hardwired in with estop)
#define goButton 10
int STOP = 0;
int buttonPress = 0;


//global variables
boolean turn = true;
int count = 0;
int number = 1;

void setup() {
  //start serial monitor
  Serial.begin(2000000);

  //set max speed for motor
  stepper.setMaxSpeed(1000);

  //set up lcd
  lcd.begin(16, 2);
  lcd.print("DEGREES: ");
  lcd.setCursor(0, 1);
  lcd.print("Rotation: ");

  //set up LEDs
  pinMode (runningLED, OUTPUT);

  //set up GO button
  pinMode(goButton, INPUT);
}

void blinkLED() { //use millis so button input is not missed
  unsigned long currentMillis = millis(); //get current time

  if (currentMillis - previousMillis >= interval) { //if interval has passed
    previousMillis = currentMillis;//save new time

    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }
  }
  digitalWrite(runningLED, ledState);//write to led

}

void reset() {
  count = 0; //set count back to zero, will try to read the button again
  buttonPress = 0; //set button state back to off


}

void loop() {
  stepper.setCurrentPosition(0);//set stepper position to zero
  stepper.setSpeed(500);//set speed of motor in steps per second
  blinkLED();//blink LED while waiting for button press
  if (count == 0) {//read button first time only, 2nd and 3rd time this will skip
    buttonPress = digitalRead(goButton);
  }
  if (buttonPress == HIGH) { //if button value is high
    digitalWrite(runningLED, HIGH);//stop blinking LED and keep solid
    if(count==0){
      lcd.setCursor(8,0);
      lcd.print("   ");
      lcd.setCursor(10,1);
      lcd.print("0");
    }
    if (count < 3) { //if less than 3 turns
      while (stepper.currentPosition() != 2048) {//while 1 turn not complete (1 turn=2048 steps)
        stepper.runSpeed();//run at specific speed
        Serial.println((stepper.currentPosition()*.1758));//print current position to serial monitor
        int position = stepper.currentPosition() * .1758; //steps into degrees *.1758
        if (position % 30 == 0) { //if position is a multiple of 30 degrees print the position
          lcd.setCursor(8, 0);
          lcd.print(position);
          lcd.print("   ");
        }
      }
      count++;//add 1 to count
      lcd.setCursor(10, 1);
      lcd.print(count);//print the count of turns
      lcd.setCursor(11, 1);
      lcd.print("/3");

    }
  }
  if (count == 3) {
    reset();
  }
}
