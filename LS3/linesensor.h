// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H
#define EMIT_PIN 11
#define DN2_PIN 18
#define DN3_PIN 20
#define DN4_PIN 21



// Class to operate the linesensor(s).
class LineSensor_c {
  public:
    unsigned long Timer_DN2 = micros();
    unsigned long Timer_DN3 = micros();
    unsigned long Timer_DN4 = micros();
    int sensor_step_DN2 = 0;
    int sensor_step_DN3 = 0;
    int sensor_step_DN4 = 0;

    //step 0 : charge capacitors and reset Timer_DN2
    //step 1 : after 10 micros, readSensorDN2, set to input, and
    //reset Timer_DN2
    //step 2 : test if pinMode is LOW, if yes, return Timer value,
    //go to step0, orelse do nothing

    int DN2_VALUE = 0;
    int DN3_VALUE = 0;
    int DN4_VALUE = 0;
  
    // Constructor, must exist.
    LineSensor_c() {
      pinMode(EMIT_PIN, OUTPUT);
      digitalWrite(EMIT_PIN,HIGH);
    } 


    //DN2 FUNCTIONS

    // You can create lots of functions, and you
    // can define them in ordinary ways to include
    // return types and arguments
    void chargecapacitor_DN2() {      
          // Charge capacitor by setting input pin
          // temporarily to output and HIGH
          pinMode( DN2_PIN, OUTPUT );
          digitalWrite( DN2_PIN, HIGH );
    }

    void startreading_DN2() {
        pinMode( DN2_PIN, INPUT );
        Timer_DN2 = micros();
    }

    int readSensorDN2() {
          if ( digitalRead( DN2_PIN ) == LOW) {
            sensor_step_DN2 = 0;
            DN2_VALUE = micros()-Timer_DN2;
            Timer_DN2 = micros();
            return DN2_VALUE;
          }
          else{
            return DN2_VALUE;
          }
      }

    int update_DN2() {

        if (sensor_step_DN2 == 0){
          chargecapacitor_DN2();
          Timer_DN2 = micros();
          sensor_step_DN2 = 1;
        }

        if (sensor_step_DN2 == 1 && micros()-Timer_DN2>10) {
          startreading_DN2();
          sensor_step_DN2 = 2;
    }
        if (sensor_step_DN2 == 2) {
          readSensorDN2();
        }
    }

    //END OF DN2 FUNCTIONS

    //DN3 FUNCTIONS

    // You can create lots of functions, and you
    // can define them in ordinary ways to include
    // return types and arguments
    void chargecapacitor_DN3() {      
          // Charge capacitor by setting input pin
          // temporarily to output and HIGH
          pinMode( DN3_PIN, OUTPUT );
          digitalWrite( DN3_PIN, HIGH );
    }

    void startreading_DN3() {
        pinMode( DN3_PIN, INPUT );
        Timer_DN3 = micros();
    }

    int readSensorDN3() {
          if ( digitalRead( DN3_PIN ) == LOW) {
            sensor_step_DN3 = 0;
            DN3_VALUE = micros()-Timer_DN3;
            Timer_DN3 = micros();
            return DN3_VALUE;
          }
          else{
            return DN3_VALUE;
          }
      }

    int update_DN3() {

        if (sensor_step_DN3 == 0){
          chargecapacitor_DN3();
          Timer_DN3 = micros();
          sensor_step_DN3 = 1;
        }

        if (sensor_step_DN3 == 1 && micros()-Timer_DN3>10) {
          startreading_DN3();
          sensor_step_DN3 = 2;
    }
        if (sensor_step_DN3 == 2) {
          readSensorDN3();
        }
    }

    //END OF DN3 FUNCTIONS

    //DN4 FUNCTIONS

    // You can create lots of functions, and you
    // can define them in ordinary ways to include
    // return types and arguments
    void chargecapacitor_DN4() {      
          // Charge capacitor by setting input pin
          // temporarily to output and HIGH
          pinMode( DN4_PIN, OUTPUT );
          digitalWrite( DN4_PIN, HIGH );
    }

    void startreading_DN4() {
        pinMode( DN4_PIN, INPUT );
        Timer_DN4 = micros();
    }

    int readSensorDN4() {
          if ( digitalRead( DN4_PIN ) == LOW) {
            sensor_step_DN4 = 0;
            DN4_VALUE = micros()-Timer_DN4;
            Timer_DN4 = micros();
            return DN4_VALUE;
          }
          else{
            return DN4_VALUE;
          }
      }

    int update_DN4() {

        if (sensor_step_DN4 == 0){
          chargecapacitor_DN4();
          Timer_DN4 = micros();
          sensor_step_DN4 = 1;
        }

        if (sensor_step_DN4 == 1 && micros()-Timer_DN4>10) {
          startreading_DN4();
          sensor_step_DN4 = 2;
    }
        if (sensor_step_DN4 == 2) {
          readSensorDN4();
        }
    }

    //END OF DN4 FUNCTIONS




};



#endif
