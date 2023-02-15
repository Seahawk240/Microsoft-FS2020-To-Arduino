#include <Stepper.h>

//////////////////////////////
////BEGIN BASIC PARAMETERS////

#define STEPPER_STEPS_PER_REVOLUTION 2048
#define STEPPER_SPEED 10

////END BASISC PARAMETERS////
/////////////////////////////

//////////////////////
////Stepper Struct////

struct stepper {
  int pos = 0;
  int nextPos = 0;
};

////Stepper Struct////
//////////////////////



//////////////////////////////
////BEGIN GLOBAL VARIABLES////

unsigned long timer = 0; //TimeOut Timer

bool flag = 0;

Stepper myStepper(STEPPER_STEPS_PER_REVOLUTION, 2, 4, 3, 5); //Variometer
stepper stepStruct;

////END GLOBAL VARIABLES////
////////////////////////////



void setup() {
  
  myStepper.setSpeed(STEPPER_SPEED);
  
  Serial.begin(115200);
  Serial.setTimeout(50);
  
  timer = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  writeToStepper ();
  getDataFromFS2020();
  writeToStepper (); 

  if (timer + 2000 < millis()) {
    timer = millis();
    if (flag) {
      Serial.print("@465/1$");
    } else {
      Serial.print("@465/0$");
    }
    flag = !flag;
 }
}


void getDataFromFS2020() {

  String input = "@";
  int value;
  int index;
  if (Serial.available() > 0) {
    Serial.readStringUntil('@'); //Look out for first Indicator
    input += Serial.readStringUntil('/') + "/"; //read the ID
    index = Serial.readStringUntil('=').toInt();
    
    if (input.indexOf("@763/") != -1) { //Check for Vertical Speed ID
      value = Serial.readStringUntil('$').toInt();  //Saves the value as int to "value" Variable for later use
      updateVariometer (value);
    }
  }
}


void writeToStepper () {
  int steps = stepStruct.nextPos - stepStruct.pos;
  //Serial.print(steps);
  if (steps > 0) {
    myStepper.step(1);
    stepStruct.pos++;
  } else if (steps < 0) {
    myStepper.step(-1);
    stepStruct.pos--;
  }
}


void updateVariometer (int feetPerMinute) {

  /* Components:
     - 1X Stepper Motor
     Positive Max 1024 = 6000 ft/min
     Negative Max -1024 = -6000 ft/min
  */

    if (feetPerMinute > 6000) feetPerMinute = 6000;
    if (feetPerMinute < -6000) feetPerMinute = -6000;
    stepStruct.nextPos = (int) ((1024.0 / 6000.0) * feetPerMinute);

}
