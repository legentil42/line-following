#include "linesensor.h"
#include "beep.h"
#include "motors.h"

#define BAUD_RATE 9600

LineSensor_c Sensors;
Beep_c Buzzer;
//Motors_c Motors;

// the setup function runs once when you press reset or power the board
void setup() {
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");

  delay(500);
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1517,100);

  delay(500);
}



void loop() {


  Sensors.white_calibration();
  Sensors.update_readings();



  // Print output.
  
  Serial.print(Sensors.DN2_NORM);
  Serial.print("," );
  Serial.print(Sensors.DN3_NORM);
  Serial.print("," );
  Serial.print(Sensors.DN4_NORM);
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
    Sensors.follow_line();
  }
