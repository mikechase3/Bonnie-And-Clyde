void setup() {
  // put your setup code here, to run once:
  int switchState = 0;
<<<<<<< HEAD
  pinMode(3,OUTPUT);
=======
  pinMode(10,OUTPUT); //10 is the pin controlling the relay.
>>>>>>> 6485ba105832e0ad21c0b5770dcb57a1f98d06e6

}

void loop() {
  // put your main code here, to run repeatedly:
<<<<<<< HEAD
  digitalWrite(3,HIGH);
  delay(1500);
  digitalWrite(3,LOW);
  delay(750);
=======
  digitalWrite(10,HIGH); //Turns on the relay for 10 seconds
  delay(10000);
  digitalWrite(10,LOW); //Prooves the resistor by turning it off every 1.5 seconds.
  delay(1500);
>>>>>>> 6485ba105832e0ad21c0b5770dcb57a1f98d06e6
}
