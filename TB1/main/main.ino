#include "linesensor.h"
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "robot_actions.h"
#define BAUD_RATE 9600

LineSensor_c Sensors;
Beep_c Buzzer;
Robot_actions_c Actions;
//Motors_c Motors;

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

  delay(500);
}



void loop() {


  Sensors.white_calibration();
  Sensors.update_readings();



  // Print output.
  
  Serial.print(count_e0);
  Serial.print("," );
  Serial.print(state_e0);
  Serial.print("," );
  Serial.print(count_e1);
  Serial.print("\n ");
  
     //if DN4 higher, L go higher
    /*
    Serial.print(Sensors.DN3_NORM);
    Serial.print("," );
    Serial.print(Sensors.DN3_VALUE);
    Serial.print("," );
    Serial.print(Sensors.WHITE_MEAN[1]);
    Serial.print("\n " );

    */
    
    Actions.go_straight();
    //Sensors.follow_line();
  }
