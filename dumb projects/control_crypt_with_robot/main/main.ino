
#include "beep.h"
#include "encoders.h"
#include "bumper.h"
#include "kinematics.h"
#define BAUD_RATE 9600


#define PI 3.1415926535897932384626433832795
Beep_c Buzzer;

BumpSensor_c Bumper;

Kinematics_c Kin;

// the setup function runs once when you press reset or power the board
void setup() {
    //Start a serial connection
    Serial.begin(BAUD_RATE);
    // Wait for stable connection, report reset.
    delay(1000);
    Serial.println("***RESET***");
    setupEncoder0();
    setupEncoder1();
    delay(500);
    Buzzer.buzz(1911,100);
    Buzzer.buzz(1517,100);
    Bumper.initialise();    
    delay(1000);

}


void loop() {
    Kin.update();
    Bumper.readBump();
    Serial.print( Kin.X);
    Serial.print(",");
    Serial.print(Kin.Y);
    Serial.print(",");
    Serial.print(Bumper.L_val);
    Serial.print(",");
    Serial.println(Bumper.R_val);
    //delay(17);
  }
      
    
    
  
