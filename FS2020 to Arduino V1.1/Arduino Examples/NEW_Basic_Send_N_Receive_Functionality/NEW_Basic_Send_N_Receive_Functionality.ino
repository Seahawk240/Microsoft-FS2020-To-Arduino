
struct DataSet {
  int id;             //ID    memory
  int index;          //Index memory
  String stringValue; //Value memory String  format
  int intValue;       //Value memory integer format
  float floatValue;   //Value memory float   format  
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  getDataFromFS2020_V1(); //Handling of the data inside the function
  DataSet newestData = getDataFromFS2020_V2(); //returns struct with the last complete DataSet received from the simulator
  //sendCommandToFS2020(465, 1); //Sends command/Import to the simulator format (ID, Value)    
}



void getDataFromFS2020_V1() {
  //Declaration of variables to store the incoming data
  int id = -1;        //ID    memory
  int index;          //Index memory
  String stringValue; //Value memory String  format
  int intValue;       //Value memory integer format
  float floatValue;   //Value memory float   format




  String temp = "";

  if (Serial.available() > 0) {
    Serial.readStringUntil('@'); //Look out for first Indicator
    id = Serial.readStringUntil('/').toInt();     //Reads ID
    index = Serial.readStringUntil('=').toInt();  //Reads index
    stringValue = Serial.readStringUntil('$');    //Reads value as String
    intValue = stringValue.toInt();               //Converts value to integer
    floatValue = stringValue.toFloat();           //Converts value to Float
  }

  switch (id) {

    case 763: //to add a new variable just add another case with your id
      //do something
      //Add whatever you want. You can get the values you want by using the
      //variables defined above:
      /*
        int id = -1;        //ID    memory
        int index;          //Index memory
        String stringValue; //Value memory String format
        float floatValue;   //Value memory float  format
      */
      break;
    case 90:
      if (intValue == 1) {
        //do something
        sendCommandToFS2020(465, 1); //Turns landing lights on when AP is on
      } else {
        //do something else
        sendCommandToFS2020(465, 0); //Turns landing lights on when AP is off
      }

      break;
    default:
      break;
  }
}


DataSet getDataFromFS2020_V2() {
  DataSet returnDataSet;
  String temp = "";

  if (Serial.available() > 0) {
    Serial.readStringUntil('@'); //Look out for first Indicator     
    returnDataSet.id = Serial.readStringUntil('/').toInt();         //Reads ID
    returnDataSet.index = Serial.readStringUntil('=').toInt();      //Reads index
    returnDataSet.stringValue = Serial.readStringUntil('$');        //Reads value as String
    returnDataSet.intValue = returnDataSet.stringValue.toInt();     //Converts value to integer
    returnDataSet.floatValue = returnDataSet.stringValue.toFloat(); //Converts value to Float
  }
  return returnDataSet;
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
