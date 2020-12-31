
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.setTimeout(50);
  // Needed for fast reaction. Could be solved by better get Data From FS2020 function
  // Only needed because of the "readStringUntil" function used. Normal Timeout = 1000ms

}

void loop() {
  getDataFromFS2020();
}


void getDataFromFS2020() {
  //Declaration of variables to store the incoming data
  String input = "@"; //General input buffer
  int value;  //Value memory
  int index;  //Index memory
 if (Serial.available() > 0) {
    Serial.readStringUntil('@'); //Look out for first Indicator
    input += Serial.readStringUntil('/') + "/"; //read the ID
    index = Serial.readStringUntil('=').toInt();    
    if (input.indexOf("@763/") != -1) { //Check for Vertical Speed ID
      value = Serial.readStringUntil('$').toInt();  //Saves the value as int to "value" Variable for later use
        
      //Do something with the values...
      //like displaying or sending something
      //Or include a function like:
      //void refreshStepperMotorPosition(int value)

    } else if (input.indexOf("@90/") != -1) { //Check for AP Master ID -> Gives Bool Value
      value = Serial.readStringUntil('$').toInt();  //Saves the value as int to "value" Variable for later use

      if (value == 1) {
        //do something
        Serial.print("@464/1$"); //Turns landing lights on when AP is on
      } else {
        //do something else
        Serial.print("@464/0$"); //Turns landing lights on when AP is off
      }
    }
  }
}
