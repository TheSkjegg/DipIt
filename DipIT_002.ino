// Description: The Great DipIT code
//
// Author: The Skjegg
//
// V000: First version
// V001: Increased debounce delay to 180, added noise filter for button
// V002: Changed IO to match Seed Studio XIAO

// IO
const int relay = 8;
const int button = 3;
const int hb_sw = 2;

int hbState = 0;
int buttonState = 0;
int switchState = 0;
int switchStateLast = 0;
int trigLevel = 200;

void setup() {
  pinMode(relay, OUTPUT); // Relay out
  pinMode(button, INPUT); // Push Button in
  pinMode(hb_sw, INPUT); // High Beam Switch in
  switchStateLast = analogRead(hb_sw);
}

void loop() {

  // Steering column high beam switch
  switchState = analogRead(hb_sw);
  if(abs(switchStateLast - switchState) > 100){
    if(switchState > trigLevel){
      digitalWrite(relay, HIGH);
      hbState = HIGH;
    }
    else{
      digitalWrite(relay, LOW);
      hbState = LOW;
    }
    switchStateLast = switchState;
  }

  // Push button
  buttonState = digitalRead(button);

  if(buttonState == LOW){ // push button pressed
    delay(50); // Noise filter
    buttonState = digitalRead(button);
    if(buttonState == LOW){
      hbState = !hbState;
      digitalWrite(relay, hbState); // Toggle HB
      //Serial.println("Button");
      while(buttonState == LOW){ // wait until button released
        buttonState = digitalRead(button);
      }
      delay(180); //Debounce wait
    }
  }
}