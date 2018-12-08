#include <IRremote.h>

const int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
}

int lastTime=0;
int time=0;
int buttonPressedTime=0;
unsigned long lastHex=0;
unsigned long hex=0;
int buttonIter=0;
String output=""

void loop() {
  if (irrecv.decode(&results)) {
    time=millis();
    hex=results.value;
    if((hex==lastHex && time-lastTime>1000) || hex!=lastHex){
      String digit=buttonPressed(hex);
      if(digit!=""){
        buttonIter++;
        
        output=output+digit;

        if(buttonIter==1){
          buttonPressedTime=time;
        }

        if(buttonIter==3){
          buttonPressedTime=time;
          Serial.println(output);
          output="";
          buttonIter=0;
        }
      }
      if(time-lastTime)
      Serial.println(out);
      
      lastTime=time;
    }

    if(time-buttonPressedTime>4000 && output!=""){
      Serial.println(output);
      buttonIter=0;
      output="";
    }

    irrecv.resume(); // Receive the next value
    lastHex=hex;
  }
}

String buttonPressed(unsigned long hex){
  String out="";
  switch(hex){
    case 0:
    case 2048:
    case 800: out="0";
              break;
    case 1:
    case 2049:
    case 801: out="1";
              break;
    case 2:
    case 2050:
    case 802: out="2";
              break;
    case 3:
    case 2051:
    case 803: out="3";
              break;
    case 4:
    case 2052:
    case 804: out="4";
              break;
    case 5:
    case 2053:
    case 805: out="5";
              break;
    case 6:
    case 2054:
    case 806: out="6";
              break;
    case 7:
    case 2055:
    case 807: out="7";
              break;
    case 8:
    case 2056:
    case 808: out="8";
              break;
    case 9:
    case 2057:
    case 809: out="9";
              break;
  }
  return out;
}