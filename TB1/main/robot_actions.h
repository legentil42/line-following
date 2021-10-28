// this #ifndef stops this file
// from being included mored than
// once by the compiler. 

#ifndef _ROBOT_ACTIONS_H
#define _ROBOT_ACTIONS_H

class Robot_actions_c {
  public:
  
    #include "motors.h"
    Motors_c Motors;
    #include "linesensor.h"
    LineSensor_c Sensors;
    #include "beep.h"
    Beep_c Buzzer;
    
    void go_straight() {
      

        Serial.print(count_e0);
        Serial.print(", ");
        Serial.println(count_e1);
        
        Sensors.white_calibration();
        Sensors.update_readings();
        
        //Buzzer.buzz(Sensors.DN2_VALUE,100);
        
        Motors.L_speedo = 50+ (-count_e0+count_e1)*1;
        Motors.R_speedo = 50+ (-count_e1+count_e0)* 1;
      
        Motors.update_motors();
        
    }


    void follow_line() {
      /*
          Serial.print(Sensors.DN4_VALUE);
          Serial.print(", ");
          Serial.print(Sensors.WHITE_MEAN[2]);
          Serial.print(", ");
          Serial.println(Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]);
          */
          Sensors.white_calibration();
          Sensors.update_readings();      
          Motors.L_speedo =  20+Sensors.DN4_NORM*0.5;// + (Sensors.DN3_NORM-100)*0.20;
          Motors.R_speedo =  20+Sensors.DN2_NORM*0.5;//  + (Sensors.DN3_NORM-100)*0.20;
          /*
          Serial.print(Sensors.DN2_NORM);
          Serial.print(", ");
          Serial.print(Sensors.DN3_NORM);
          Serial.print(", ");
          Serial.println(Sensors.DN4_NORM);
          */
          if (Sensors.DN4_NORM> Sensors.DN3_NORM && Sensors.DN4_NORM> Sensors.DN2_NORM) { Motors.R_speedo = -20;}
          if (Sensors.DN2_NORM> Sensors.DN3_NORM && Sensors.DN2_NORM> Sensors.DN4_NORM) { Motors.L_speedo = -20;}
          Motors.update_motors();

    }



    bool check_for_line() {

        if (Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]> 500 && Sensors.DN3_VALUE-Sensors.WHITE_MEAN[1]> 500 && Sensors.DN2_VALUE-Sensors.WHITE_MEAN[0]> 500){
            return true;
        }
        else {return false;}
        
    }

};

#endif
