#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Pot Resistance: Across the top: 9.54K(ohms)
//Pot Resistance: Total amount of resistance for contrast: 8.93kilo-oms.

const int receiver = 7;
int play_pause = 0;

//Defines the Strings
char whichButtonIsPressed[] = {'n', 'o', 't', 'h', 'i', 'n', 'g', 'I', 's', 'H', 'e', 'r', 'e', 'Y', 'e', 't'}; 

// declare objects
IRrecv irrecv(receiver); //Creat an instance of 'irrecv'
decode_results results; //Create instance of 'decode_results'

void translateIR() {
  // decribing remote IR codes

  switch(results.value) {
    case 0xFFA25D:
      Serial.println("POWER");
      digitalWrite(8,LOW); //Puts the string "POWER" into the whichButtonIsPressed array.
      whichButtonIsPressed[0] = 'P';
      whichButtonIsPressed[1] = 'O';
      whichButtonIsPressed[2] = 'W';
      whichButtonIsPressed[3] = 'E';
      whichButtonIsPressed[4] = 'R';
      for (int i = 5; i<16; i++){
        whichButtonIsPressed[i] = ' ';
      }
        stringPrint();
      break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("Fast Back"); break;
    case 0xFF02FD:
      Serial.println("PAUSE/PLAY");
      if (play_pause == 0) {
        play_pause = 1;
        digitalWrite(8,HIGH);
      }
      else if (play_pause == 1) {
        play_pause = 0;
        digitalWrite(8,LOW);
      }
      break;
    case 0xFFC23D: Serial.println("FAST FORWARD"); break;
    case 0xFFE01F: Serial.println("DOWN"); break;
    case 0xFFA857: Serial.println("VOL -"); break;
    case 0xFF906F: Serial.println("UP"); break;
    case 0xFF9867: Serial.println("EQ"); break;
    case 0xFFB04F: Serial.println("ST/REPT"); break;
    // Start Numbers and Digits
    case 0xFF6897: Serial.println("0"); break;
    case 0xFF30CF:
      Serial.println("1 - 10 seconds");
      digitalWrite(8,HIGH);
      delay(10000);
      break;
    case 0xFF18E7: Serial.println("2"); break;
    case 0xFF7A85: Serial.println("3"); break;
    case 0xFF10EF: Serial.println("4"); break;
    case 0xFF38C7: Serial.println("5"); break;
    case 0xFF5AA5: Serial.println("6"); break;
    case 0xFF42BD: Serial.println("7"); break;
    case 0xFF4AB5: Serial.println("8"); break;
    case 0xFF52AD: Serial.println("9"); break;

    case 0xFFFFFFFF: Serial.println(" REPEAT"); break; //Repeats the same digit.

    default:
    Serial.println(" other button ");
  } //End of case
  delay(500);
}


//Prints the string
void stringPrint() {
  /*
  char topHalfLCD[] = "Mike Chase & Evn"; //You can only display 16 digits on the top LCD
  char bottomHalfLCD[] = "Bottom Half Cool"; //Same with the bottom.
  bottomHalfLCD[16] = whichButtonIsPressed[16]; //The bottom half of the display should display which button is pressed. (Currently only with power).
  lcd.print(topHalfLCD);
  */
  lcd.setCursor(0,1);
  //lcd.print(bottomHalfLCD);
  lcd.print(whichButtonIsPressed);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); //Start the receiver.
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  lcd.begin(16,2); //Initializes the baord as 2 rows 16 across.
  stringPrint();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) //Have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); //Receive the next value
  }

}
