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
    unsigned long Timer_charge = micros();
    int sensor_step = 0;
    bool done2 = false;
    bool done3 = false;
    bool done4 = false;
    unsigned long reading_timer = micros();

    unsigned long elapsed_time;
    //step 0 : charge capacitors and reset Timer_charge
    //step 1 : after 10 micros, readSensors, set to input, and
    //reset start time for readings
    //step 2 : test if pin is LOW, if yes, return Timer value,
    //go to step0, orelse do nothing

    unsigned long DN2_VALUE = 0;
    unsigned long DN3_VALUE = 0;
    unsigned long DN4_VALUE = 0;

    float WHITE_MEAN[3] = {0,0,0} ;
    float BLACK_MEAN[3] = {1,1,1} ;

    float DN2_NORM;
    float DN3_NORM;
    float DN4_NORM;
  
    // Constructor, must exist.
    LineSensor_c() {
      pinMode(EMIT_PIN, OUTPUT);
      digitalWrite(EMIT_PIN,HIGH);
    } 


    // You can create lots of functions, and you
    // can define them in ordinary ways to include
    // return types and arguments
    void chargecapacitors() {      
          // Charge capacitor by setting input pin
          // temporarily to output and HIGH
          pinMode( DN2_PIN, OUTPUT );
          pinMode( DN3_PIN, OUTPUT );
          pinMode( DN4_PIN, OUTPUT );
          digitalWrite( DN2_PIN, HIGH );
          digitalWrite( DN3_PIN, HIGH );
          digitalWrite( DN4_PIN, HIGH );
    }

    void startreading() {
        pinMode( DN2_PIN, INPUT );
        pinMode( DN3_PIN, INPUT );
        pinMode( DN4_PIN, INPUT );
        done2 = false;
        done3 = false;
        done4 = false;
        
    }

    void readSensors() {

          while (done2 == false || done3 == false || done4 == false) {
          if (done2 == false && digitalRead( DN2_PIN ) == LOW ) {
            DN2_VALUE = micros()-reading_timer;
            done2 = true;
          }

          if (done3 == false && digitalRead( DN3_PIN ) == LOW ) {
            DN3_VALUE = micros()-reading_timer;
            done3 = true;
          }

          if (done4 == false && digitalRead( DN4_PIN ) == LOW ) {
            DN4_VALUE = micros()-reading_timer;
            done4 = true;
          }
          }
          if (done2 == true && done3 == true && done4 == true) {
              sensor_step = 0;
                DN2_NORM = (DN2_VALUE - WHITE_MEAN[0])/BLACK_MEAN[0];
                DN3_NORM = (DN3_VALUE - WHITE_MEAN[1])/BLACK_MEAN[1];
                DN4_NORM = (DN4_VALUE - WHITE_MEAN[2])/BLACK_MEAN[2];
          }
      }


    void update_readings() {

        if (sensor_step == 0){
          chargecapacitors();
          Timer_charge = micros();
          sensor_step = 1;
        }

        if (sensor_step == 1 && micros()-Timer_charge>10) {
          startreading();
          sensor_step = 2;
          reading_timer = micros();
    }
        if (sensor_step == 2) {
          readSensors();
        }
    }


    void white_calibration(){

        for (int i = 0; i < 100; i++) {
            update_readings();
            WHITE_MEAN[0] = WHITE_MEAN[0] + DN2_VALUE;
            WHITE_MEAN[1] = WHITE_MEAN[1] + DN3_VALUE;
            WHITE_MEAN[2] = WHITE_MEAN[2] + DN4_VALUE;
          }
          
        WHITE_MEAN[0] = WHITE_MEAN[0]/100;
        WHITE_MEAN[1] = WHITE_MEAN[1]/100;
        WHITE_MEAN[2] = WHITE_MEAN[2]/100;
              
    }

    void find_black_line() { // robot go forward until it finds a line
     while (DN2_VALUE < 2000 && DN3_VALUE < 2000 && DN4_VALUE < 2000){
        update_readings();
     }
    }


    void black_calibration() {
       for (int i = 0; i < 5; i++) {
            update_readings();
            BLACK_MEAN[0] = BLACK_MEAN[0] + DN2_VALUE - WHITE_MEAN[0];
            BLACK_MEAN[1] = BLACK_MEAN[1] + DN3_VALUE - WHITE_MEAN[1];
            BLACK_MEAN[2] = BLACK_MEAN[2] + DN4_VALUE - WHITE_MEAN[2];
          }
        BLACK_MEAN[0] = BLACK_MEAN[0]/5;
        BLACK_MEAN[1] = BLACK_MEAN[1]/5;
        BLACK_MEAN[2] = BLACK_MEAN[2]/5;

    }
};



#endif
