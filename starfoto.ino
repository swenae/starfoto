/*****************************************************************************
  This is the "starfoto" sketch.

  Module        : main module, starfoto.ino
  Author        : Swen Hopfe (dj)
  Design        : 2019-01-30
  Last modified : 2019-01-31

  It works with ESP32, NEMA17 stepper with 1:26.85 gear and
  stepper driver DRV8825. It was tested with ESP32-ST, with
  wiring for a WEMOS LOLIN32 board.

 ****************************************************************************/

    // pins for stepper control
    const int stepPin = 16;
    const int dirPin = 17;

    // number of max shots/steps
    const int ns = 20;
    // counter of shots/steps
    int z = 0;

//-----------------------------------------------------------------

    void setup() {

      // set the control pins to output
      pinMode(stepPin,OUTPUT);
      pinMode(dirPin,OUTPUT);
      delay(100);

      // set a particular direction (clockwise)
      digitalWrite(dirPin,LOW);
      delay(1000);

    }

//-----------------------------------------------------------------

    void loop() {

      //-------------------------------------------------------

      /*
      // highspeed test
      // 26.85 * 200 full steps = 5370 times * 1.8 degrees
      // for a full cycle with our 1:26.85 gear
      // and takes us 5370 * 4ms = 5.4 seconds

      digitalWrite(dirPin,LOW); // turn clockwise
      delayMicroseconds(500);

      for(int x = 0; x < 5370; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }

      delay(5000);
      */

      //-------------------------------------------------------

      // normal operation
      // virtual sky turns 360°/24h clockwise
      // stepper without gear runs with 1.8°/step = 200steps/360°cycle
      // 200steps/24h(24*3600s=86400s) are equal to 1step/432s
      // that means for sky speed we need 1 step every 432 seconds
      // with 1:26.85 gear we need 1 step every 16.089385475 seconds
      // because with gear we only do 0.067039106°/step

      z++;

      digitalWrite(dirPin,LOW); // turn clockwise
      delayMicroseconds(16088385); // 16089385µs - 1000µs = 16088385µs

      // before the next step
      // we have approx 16 seconds to do the camera shot now
      // so we program the camera to this interval
      // all exposure times below this are possible for the current fotograph
      // nevertheless it is not exactly 16s, we will not run into problems
      // because of the fact that there are only some shots to do
      // we expect less than 20 shots only...

      if (z <= ns) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }

    }
//----------------------------------------------------------------------------
