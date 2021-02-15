#include "Keyboard.h"


int timedown[8];
int pressed[8];
int sent[8];

// the setup routine runs once when you press reset:
void setup() {
  Keyboard.begin();
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the pushbutton's pin an input:
  for (int i=0; i<8; ++i) {
    timedown[i] = 0;
    pressed[i] = 0;
    sent[i] = 0;
    pinMode(2+i, INPUT_PULLUP);  
  }
}

int n=0;

// the loop routine runs over and over again forever:
void loop() {
  for (int i=0; i<8; ++i) {
    if (digitalRead(2+i) == 0) {
      timedown[i] += 1;
      if (timedown[i] > 20) {
        timedown[i] = 20;
        pressed[i] = 1;
        if (!sent[i]) {
          sent[i] = 1;
          if (i==0) {
            Keyboard.press('r');
          } else if (i==1) {
            Keyboard.press(' ');
          } else if (i==2) {
            Keyboard.press(KEY_RETURN);
          } else if (i==3) {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('r');
            Keyboard.release(KEY_LEFT_CTRL);
          }
        }
      }
    } else {
      timedown[i] = 0;
      pressed[i] = 0;
      if (sent[i]) {
        sent[i] = 0;
        if (i==0) {
          Keyboard.release('r');
        } else if (i==1) {
          Keyboard.release(' ');
        } else if (i==2) {
          Keyboard.release(KEY_RETURN);
        } else if (i==3) {
          Keyboard.release('r');
        }
      }
    }
    if (n % 100 == 0) {
      Serial.print(pressed[i]);
    }
  }
  if (n % 100 == 0) {
    Serial.println();
  }
  ++n;
  delay(1);        // delay in between reads for stability
}
