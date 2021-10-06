/* Classic Mini Fan controller

    (C) A.G.Doswell 2021

    Runs on a Tiny 85, or almost anything else, and uses the standard temp sender in the cylinder head. Doesn't upset the existing gauge.

    Schematic at andydoz.blosgpot.com
*/

#include <avr/io.h>
#define setPoint 512
#define time_limit 30000 // time fan is left running after temperature drops below threshold.
unsigned long cumulative;
unsigned int average;
unsigned long timer;

void setup() {
  pinMode (0, OUTPUT);
  pinMode (1, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
}
void loop() {
  for (int i = 0; i <= 99; i++) { //get 100 samples
    cumulative += analogRead(A1);
  }
  average = cumulative / 100;// average them out
  cumulative = 0;
  if (average < 512) { // if the average is less than 512, set the fan timer running, and switch the instantanious LED on
    timer = millis();
    digitalWrite (0, HIGH);
  }
  else {
    digitalWrite(0, LOW); // if the average is greater than 512, switch the instantanious LED off.
  }
  if ((millis() - timer) < time_limit) { // if the timer is running, switch the fan on
    digitalWrite(1, HIGH);
  }
  else {
    digitalWrite(1, LOW); // if the timer isn't runing switch the fan off.
  }
}
