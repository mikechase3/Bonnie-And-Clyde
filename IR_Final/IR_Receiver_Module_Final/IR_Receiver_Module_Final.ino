#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <LiquidCrystal.h>

// global variables
const int receiver = 7;
int play_pause = 0;
double time_left = 0.0;
bool isPreset = false;

// declare objects
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
IRrecv irrecv(receiver); //Create an instance of 'irrecv'
decode_results results; //Create instance of 'decode_results'

void translateIR() {
  // decribing remote IR codes

  switch(results.value) {
    case 0xFFA25D:
      Serial.println("POWER");
      lcd.clear();
      lcd.print("POWER");
      digitalWrite(8,LOW);
      isPreset = false;
      time_left = 0;
      play_pause = 0;
      break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); lcd.clear(); lcd.print("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); lcd.clear(); lcd.print("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK"); lcd.clear(); lcd.print("FAST BACK"); break;
    case 0xFF02FD:
      if (!isPreset) {
        Serial.println("PAUSE/PLAY");
        lcd.clear();
        lcd.print("PAUSE/PLAY");
        if (play_pause == 0) {
          play_pause = 1;
          digitalWrite(8,HIGH);
        }
        else if (play_pause == 1) {
          play_pause = 0;
          digitalWrite(8,LOW);
        }
      }
      else {
        Serial.println("PRESET ON - PRESS POWER");
      }
      break;
    case 0xFFC23D: Serial.println("FAST FORWARD"); lcd.clear(); lcd.print("FAST FORWARD"); break;
    case 0xFFE01F: Serial.println("DOWN"); lcd.clear(); lcd.print("DOWN"); break;
    case 0xFFA857: Serial.println("VOL -"); lcd.clear(); lcd.print("VOL-"); break;
    case 0xFF906F: Serial.println("UP"); lcd.clear(); lcd.print("UP"); break;
    case 0xFF9867: Serial.println("EQ"); lcd.clear(); lcd.print("EQ"); break;
    case 0xFFB04F: Serial.println("ST/REPT"); lcd.clear(); lcd.print("ST/REPT"); break;
    // Start Numbers and Digits
    case 0xFF6897: Serial.println("0"); lcd.clear(); lcd.print("0"); break;
    case 0xFF30CF:
      Serial.println("1 - 10 seconds");
      lcd.clear();
      lcd.print("10 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 10;
      break;
    case 0xFF18E7:
      Serial.println("2 - 60 seconds - 1 minute");
      lcd.clear();
      lcd.print("60 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 60;
      break;
    case 0xFF7A85:
      Serial.println("3 - 120 seconds - 2 minutes");
      lcd.clear();
      lcd.print("120 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 120;
      break;
    case 0xFF10EF:
      Serial.println("4 - 300 seconds - 5 minutes");
      lcd.clear();
      lcd.print("300 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 300;
      break;
    case 0xFF38C7:
      Serial.println("5 - 900 seconds - 15 minutes");
      lcd.clear();
      lcd.print("900 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 900;
      break;
    case 0xFF5AA5:
      Serial.println("6 - 1800 seconds - 30 minutes");
      lcd.clear();
      lcd.print("1800 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 1800;
      break;
    case 0xFF42BD:
      Serial.println("7 - 3600 seconds - 60 minutes - 1 hour");
      lcd.clear();
      lcd.print("3600 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 3600;
      break;
    case 0xFF4AB5:
      Serial.println("8 - 7200 seconds - 120 minutes - 2 hours");
      lcd.clear();
      lcd.print("7200 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 7200;
      break;
    case 0xFF52AD:
      Serial.println("9 - 86400 seconds - 720 minutes - 12 hours");
      lcd.clear();
      lcd.print("86400 SECONDS");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 86400;
      break;

    case 0xFFFFFFFF: Serial.println(" REPEAT"); break; //Repeats the same digit.

    default:
    Serial.println(" other button ");
  } //End of case
  delay(500);
}

void refresh() {
  lcd.clear();

  // first line
  lcd.setCursor(0,0);
  lcd.print("Door is ");
  lcd.setCursor(8,0);
  if (!isPreset || play_pause == 1) {
    lcd.print("LOCKED");
  }
  else {
    lcd.print("UNLOCKED");
  }

  // second line
  lcd.setCursor(0,1);
  if (isPreset) {
    lcd.print("Lock in ");
    lcd.setCursor(8,1);
    lcd.print(String(time_left)); // TODO Check this
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); //Start the receiver.
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);

  // lcd setup
  lcd.begin(16,2); //Initializes the baord as 2 rows 16 across.
  lcd.setCursor(0,0);
  lcd.print("Welcome to")
  lcd.setCursor(0,1);
  lcd.print("Bonnie & Clyde");
  delay(3000);
  refresh();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) //Have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); //Receive the next value
  }
  if (isPreset) {
    if (time_left == 0.0) {
      digitalWrite(8,LOW);
      isPreset = false;
    }
    else {
      time_left = time_left - 0.5;
      Serial.println(time_left);
      delay(500);
    }
  }
  refresh();
}
