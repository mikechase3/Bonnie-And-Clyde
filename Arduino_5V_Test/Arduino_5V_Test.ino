void setup() {
  // put your setup code here, to run once:
  int switchState = 0;
  pinMode(10,OUTPUT); //10 is the pin controlling the relay.

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10,HIGH); //Turns on the relay for 10 seconds
  delay(10000);
  digitalWrite(10,LOW); //Prooves the resistor by turning it off every 1.5 seconds.
  delay(1500);
}
