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

float WHITE_MEAN[3] = {0,0,0} ;
float BLACK_MEAN[3] = {0,0,0} ;

float DN2_NORM;
float DN3_NORM;
float DN4_NORM;


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
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
  for (int i = 0; i < 100; i++) {
    Sensors.update_readings();
    WHITE_MEAN[0] = WHITE_MEAN[0] + Sensors.DN2_VALUE;
    WHITE_MEAN[1] = WHITE_MEAN[1] + Sensors.DN3_VALUE;
    WHITE_MEAN[2] = WHITE_MEAN[2] + Sensors.DN4_VALUE;
  }
  WHITE_MEAN[0] = WHITE_MEAN[0]/100;
  WHITE_MEAN[1] = WHITE_MEAN[1]/100;
  WHITE_MEAN[2] = WHITE_MEAN[2]/100;

  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
  Motors.L_speedo = 50;
  Motors.R_speedo = 50;
  Motors.update_motors();
  Sensors.update_readings();
  DN2_NORM = Sensors.DN2_VALUE - WHITE_MEAN[0];
  DN3_NORM = Sensors.DN3_VALUE - WHITE_MEAN[1];
  DN4_NORM = Sensors.DN4_VALUE - WHITE_MEAN[2];
  
  while (DN2_NORM < 1500 && DN3_NORM < 1500 && DN4_NORM < 1500){
    Sensors.update_readings();
    DN2_NORM = Sensors.DN2_VALUE - WHITE_MEAN[0];
    DN3_NORM = Sensors.DN3_VALUE - WHITE_MEAN[1];
    DN4_NORM = Sensors.DN4_VALUE - WHITE_MEAN[2];
  }
  
  Motors.L_speedo = 0;
  Motors.R_speedo = 0;
  Motors.update_motors();
  
  delay(1000);
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
   for (int i = 0; i < 100; i++) {
    Sensors.update_readings();
    BLACK_MEAN[0] = BLACK_MEAN[0] + Sensors.DN2_VALUE - WHITE_MEAN[0];
    BLACK_MEAN[1] = BLACK_MEAN[1] + Sensors.DN3_VALUE - WHITE_MEAN[1];
    BLACK_MEAN[2] = BLACK_MEAN[2] + Sensors.DN4_VALUE - WHITE_MEAN[2];
  }
  BLACK_MEAN[0] = BLACK_MEAN[0]/100;
  BLACK_MEAN[1] = BLACK_MEAN[1]/100;
  BLACK_MEAN[2] = BLACK_MEAN[2]/100;
  
  
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1517,100);
  Buzzer.buzz(1276,100);
}



void loop() {

  //Motors.update_motors();

  Sensors.update_readings();
  DN2_NORM = (Sensors.DN2_VALUE - WHITE_MEAN[0])/BLACK_MEAN[0];
  DN3_NORM = (Sensors.DN3_VALUE - WHITE_MEAN[1])/BLACK_MEAN[1];
  DN4_NORM = (Sensors.DN4_VALUE - WHITE_MEAN[2])/BLACK_MEAN[2];

  // Print output.
  Serial.print( DN2_NORM);
  Serial.print("," );
  Serial.print( DN3_NORM);
  Serial.print("," );
  Serial.print(DN4_NORM);
  Serial.print("\n ");
  
 
  }
