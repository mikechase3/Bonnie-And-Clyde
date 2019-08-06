int buttonIsClicked = 0;

void setup() {
  // put your setup code here, to run once:
  int switchState = 0;
  for (int i = 2; i<=7; i++){ //inputs 2-7 are inputs.
    pinMode(i,INPUT);
  }

  for (int i = 8; i<=13; i++){ //8-13 are now outputs
    pinMode(i,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonIsClicked = digitalRead(7);
  digitalWrite(10,HIGH);
  if(buttonIsClicked == HIGH){
    digitalWrite(8,HIGH); //Turns relay on
    delay(1000); 
    digitalWrite(8,LOW); //Turns the relay off.
  }


}
