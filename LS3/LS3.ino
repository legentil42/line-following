#include "linesensor.h"
#include "beep.h"
#include "motors.h"

#define BAUD_RATE 9600

LineSensor_c Sensors;
Beep_c Buzzer;
Motors_c Motors;
bool Met_Line = false;
float max1;
float max2;
float max3;

// the setup function runs once when you press reset or power the board
void setup() {
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");

  delay(2000);
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
  Sensors.white_calibration();


  
  Motors.L_speedo = 30;
  Motors.R_speedo = 30;
  Motors.update_motors();
  Sensors.find_black_line();

  Motors.L_speedo = 20;
  Motors.R_speedo = 20;
  Motors.update_motors();
  max1 = Sensors.DN2_VALUE;
  max2 = Sensors.DN3_VALUE;
  max3 = Sensors.DN4_VALUE;
  
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
  for (int i = 0; i < 100; i++) {
    Sensors.update_readings();
    max1 = max(Sensors.DN2_VALUE,max1);
    max2 = max(Sensors.DN3_VALUE,max2);
    max3 = max(Sensors.DN4_VALUE,max3);
    delay(10);
  }
  
  Motors.L_speedo = 0;
  Motors.R_speedo = 0;
  Motors.update_motors();

  Sensors.BLACK_MEAN[0] = max1;
  Sensors.BLACK_MEAN[1] = max2;
  Sensors.BLACK_MEAN[2] = max3;
  
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1911,100);
  
  Buzzer.buzz(1911,100);
  Buzzer.buzz(1517,100);
  Buzzer.buzz(1276,100);
  delay(500);
}



void loop() {



  Sensors.update_readings();



  // Print output.
  /*
  Serial.print(Sensors.DN2_NORM);
  Serial.print("," );
  Serial.print(Sensors.DN3_NORM);
  Serial.print("," );
  Serial.print(Sensors.DN4_NORM);
  Serial.print("," );
  Serial.print(Sensors.BLACK_MEAN[0]);
  Serial.print("," );
  Serial.print(Sensors.BLACK_MEAN[1]);
  Serial.print("," );
  Serial.print(Sensors.BLACK_MEAN[2]);
  Serial.print("\n ");
  */
     //if DN4 higher, L go higher

    Serial.println(-Sensors.DN2_NORM+Sensors.DN4_NORM);

    Motors.L_speedo =  Sensors.DN4_NORM*60 -Sensors.DN2_NORM*40 + (Sensors.DN3_NORM-0.45)*50 + Sensors.DN3_NORM*20;
    Motors.R_speedo =  Sensors.DN2_NORM*60 -Sensors.DN4_NORM*40 + (Sensors.DN3_NORM-0.45)*50 + Sensors.DN3_NORM*20;
    
    Motors.update_motors();
  }
