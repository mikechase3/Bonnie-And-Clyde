#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int receiver = 7;
int play_pause = 0;
double time_left = 0.0;
bool isPreset = false;

// declare objects
IRrecv irrecv(receiver); //Create an instance of 'irrecv'
decode_results results; //Create instance of 'decode_results'

void translateIR() {
  // decribing remote IR codes

  switch(results.value) {
    case 0xFFA25D:
      Serial.println("POWER");
      digitalWrite(8,LOW);
      isPreset = false;
      time_left = 0;
      play_pause = 0;
      break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("Fast Back"); break;
    case 0xFF02FD:
      if (!isPreset) {
        Serial.println("PAUSE/PLAY");
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
      isPreset = true;
      play_pause = 0;
      time_left = 10;
      break;
    case 0xFF18E7:
      Serial.println("2 - 60 seconds - 1 minute");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 60;
      break;
    case 0xFF7A85:
      Serial.println("3 - 120 seconds - 2 minutes");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 120;
      break;
    case 0xFF10EF:
      Serial.println("4 - 300 seconds - 5 minutes");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 300;
      break;
    case 0xFF38C7:
      Serial.println("5 - 900 seconds - 15 minutes");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 900;
      break;
    case 0xFF5AA5:
      Serial.println("6 - 1800 seconds - 30 minutes");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 1800;
      break;
    case 0xFF42BD:
      Serial.println("7 - 3600 seconds - 60 minutes - 1 hour");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 3600;
      break;
    case 0xFF4AB5:
      Serial.println("8 - 7200 seconds - 120 minutes - 2 hours");
      digitalWrite(8,HIGH);
      isPreset = true;
      play_pause = 0;
      time_left = 7200;
      break;
    case 0xFF52AD:
      Serial.println("9 - 86400 seconds - 720 minutes - 12 hours");
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); //Start the receiver.
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);

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
}
