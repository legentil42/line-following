#include "linesensor.h"
#include "beep.h"
#include "motors.h"

#define BAUD_RATE 9600

LineSensor_c Sensors;
Beep_c Buzzer;
Motors_c Motors;
bool Met_Line = false;


unsigned long value2;
unsigned long value3;
unsigned long value4;
// the setup function runs once when you press reset or power the board
void setup() {
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
unsigned long tmp = micros();
void loop() {

  Sensors.update_readings();
  //Motors.update_motors();
     
  // Print output.
  
  Serial.print(micros()-tmp);
  value2 = Sensors.DN2_VALUE;
  value3 = Sensors.DN3_VALUE;
  value4 = Sensors.DN4_VALUE;
  tmp = micros();
  Serial.print("   ");
  Serial.print(" DN2,3,4: " );
  Serial.print( value2);
  Serial.print("," );
  Serial.print( value3);
  Serial.print("," );
  Serial.print(value4);
  Serial.print("\n ");
  
 
  }
