
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  
  //IDENT Function
  Serial.print("@9999/Arduino IDENT Example$");
  sendCommandToFS2020(9999, "Arduino IDENT Example");
  //Sends the program a note, that it wants to work with it and send a identifier.
}

void loop() {
  
  //Basic Import
  Serial.print("@465/1$");
  sendCommandToFS2020(465,1);
  //Turns Landing Light On
  
  delay(1000);
  
  //Button Import
  Serial.print("@10043/$");
  sendCommandToFS2020(10043);
  //Presses Keyboard Button 'G'
  
  delay(1000);
  
  //Custom Import
  Serial.print("@10000/LANDING_LIGHTS_SET;0");
  sendCommandToFS2020(10000,"LANDING_LIGHTS_SET;0");
  //Turns Landing Light Off

  delay(1000);
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

void sendCommandToFS2020(int id) {
  String output =  "@" + String(id) + "/$";
  Serial.print(output);
}
