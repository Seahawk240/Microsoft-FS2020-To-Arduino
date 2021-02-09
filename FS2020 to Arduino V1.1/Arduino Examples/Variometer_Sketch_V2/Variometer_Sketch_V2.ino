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
  //writeToStepper ();

  if (timer + 2000 < millis()) {
    timer = millis();
    if (flag) {
      sendCommandToFS2020(465, 1);
    } else {
      sendCommandToFS2020(465, 0);
    }
    flag = !flag;
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







void getDataFromFS2020() {
  //Declaration of variables to store the incoming data
  int id = -1;        //ID    memory
  int index;          //Index memory
  String stringValue; //Value memory String  format
  int intValue;       //Value memory integer format
  float floatValue;   //Value memory float   format
  //bool worked = 0;    //Integrity variable




  String temp = "";

  if (Serial.available() > 0) {
    Serial.readStringUntil('@'); //Look out for first Indicator
    //temp += Serial.readStringUntil('/'); //read the ID
    //id = temp.toInt();
    id = Serial.readStringUntil('/').toInt();
    index = Serial.readStringUntil('=').toInt();
    stringValue = Serial.readStringUntil('$');
    intValue = stringValue.toInt();
    floatValue = stringValue.toFloat();
  }

  switch (id) {


    case 763: //to add a new variable just add another case with you id
      updateVariometer (intValue);
      break;
      
    default:
      break;
  }
}




void sendCommandToFS2020(int id, int value) {
  String output =  "@" + String(id) + "/" + String(value) + "$";
  Serial.print(output);
}

void sendCommandToFS2020(int id, double value) {
  String output =  "@" + String(id) + "/" + String(value) + "$";
  Serial.print(output);
}

void sendCommandToFS2020(int id, float value) {
  String output =  "@" + String(id) + "/" + String(value) + "$";
  Serial.print(output);
}

void sendCommandToFS2020(int id, String value) {
  String output =  "@" + String(id) + "/" + String(value) + "$";
  Serial.print(output);
}

void sendCommandToFS2020(String id, String value) {
  String output =  "@" + id + "/" + value + "$";
  Serial.print(output);
}
