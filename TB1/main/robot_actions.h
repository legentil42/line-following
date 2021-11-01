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
    #include "kinematics.h"
    Kinematics_c Kin;
    bool is_on_line = false;
    unsigned long lost_line_time = millis();
    
    
    void go_straight() {
      
        Kin.update();
          /*
          Serial.print(Sensors.DN2_VALUE-Sensors.WHITE_MEAN[0]);
          Serial.print(", ");
          Serial.print(Sensors.DN3_VALUE-Sensors.WHITE_MEAN[1]);
          Serial.print(", ");
          Serial.println(Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]);
          */
        Sensors.white_calibration();
        Sensors.update_readings();/*
        Serial.print(count_e0);
        Serial.print(", ");
        Serial.println(count_e1);*/
        //Buzzer.buzz(Sensors.DN2_VALUE,100);
        
        Motors.L_speedo = 30+ (count_e0-count_e1)*1;
        Motors.R_speedo = 30+ (count_e1-count_e0)* 1;
      
        Motors.update_motors();
        
    }

    void turn_on_spot() {
       
        float old_theta = Kin.theta;
        reset_count();
        while (Kin.theta-old_theta < 3) {
        Motors.L_speedo = 30+ (abs(count_e0)-abs(count_e1))*1;
        Motors.R_speedo = -30- (abs(count_e1)-abs(count_e0))* 1;
        Motors.update_motors();
        Kin.update();
        }
        reset_count();
    }

    void follow_line() {

          Sensors.white_calibration();
          Sensors.update_readings();      
          Motors.L_speedo =  20+Sensors.DN4_NORM*0.5;// + (Sensors.DN3_NORM-100)*0.20;
          Motors.R_speedo =  20+Sensors.DN2_NORM*0.5;//  + (Sensors.DN3_NORM-100)*0.20;
          
          Serial.print(Sensors.DN2_VALUE-Sensors.WHITE_MEAN[0]);
          Serial.print(", ");
          Serial.print(Sensors.DN3_VALUE-Sensors.WHITE_MEAN[1]);
          Serial.print(", ");
          Serial.println(Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]);
          
          if (Sensors.DN4_NORM> Sensors.DN3_NORM && Sensors.DN4_NORM> Sensors.DN2_NORM) { Motors.R_speedo = -20;}
          if (Sensors.DN2_NORM> Sensors.DN3_NORM && Sensors.DN2_NORM> Sensors.DN4_NORM) { Motors.L_speedo = -20;}
          Motors.update_motors();

    }


    void reset_count() {
        count_e0 = 0;
        count_e1 = 0;
        Kin.old_e1 = 0;
        Kin.old_e0 = 0;
    }


    bool check_for_line() {
      Sensors.update_readings();  
      
        if (Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]> 800 && Sensors.DN3_VALUE-Sensors.WHITE_MEAN[1]> 800 && Sensors.DN2_VALUE-Sensors.WHITE_MEAN[0]> 800){
            is_on_line = true;
            return true;
        }
        else if (Sensors.DN4_VALUE-Sensors.WHITE_MEAN[2]< 800 && Sensors.DN3_VALUE-Sensors.WHITE_MEAN[1]< 800 && Sensors.DN2_VALUE-Sensors.WHITE_MEAN[0]< 800)
        { 
          if (is_on_line == true) {
                lost_line_time = millis();
                is_on_line = false;
          }
          
                
          return false;}
        
    }

    void go_X_distance(float desired_X) {
      
        Kin.update();
        reset_count();
        float old_X = Kin.X;
        while (Kin.X-old_X < desired_X) {
        Kin.update();
        Serial.print(Kin.X-old_X);
        Serial.print(" ,");
        Serial.println("going");
        Motors.L_speedo = 30+ (count_e0-count_e1)*1;
        Motors.R_speedo = 30+ (count_e1-count_e0)* 1;
      
        Motors.update_motors();
        }
        Motors.L_speedo = 0;
        Motors.R_speedo = 0;
      
        Motors.update_motors();
    }

    void show_pos() {

      Kin.update();
    }
};

#endif
