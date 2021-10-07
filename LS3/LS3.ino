
#include "linesensor.h"
#include "beep.h"
#include "motors.h"

#define BAUD_RATE 9600
// Pin definitions, to make the
// code easier to read.



//variable for time managment
LineSensor_c Sensors;
Beep_c Buzzer;
Motors_c Motors;

// the setup function runs once when you press reset or power the board
void setup() {
  // Set our motor driver pins as outputs.

  
  
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");
  //play sound:
  //Buzzer.buzz(1276,200);
  //Buzzer.buzz(1517,200);
  //Buzzer.buzz(1911,100);
  //Buzzer.buzz(1517,100);
  //Buzzer.buzz(1276,100);
  delay(2000);

}

void loop() {

  Sensors.update_DN2();
  Sensors.update_DN3();
  Sensors.update_DN4(); 
  Motors.update_motors();
     
  // Print output.
  //Serial.print("DN2,3,4: " );
  //Serial.print( Sensors.DN2_VALUE);
  //Serial.print("," );
  //Serial.print( Sensors.DN3_VALUE);
  //Serial.print("," );
  //Serial.print( Sensors.DN4_VALUE);
  Serial.println(Motors.L_speedo);

  Motors.L_speedo = Motors.L_speedo +10;
  delay(100);


  }
