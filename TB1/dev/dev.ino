
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "robot_actions.h"
#include "kinematics.h"
#include "pid.h"
#include "linesensor.h"
#define BAUD_RATE 9600
#define state_find_line 0
#define state_follow_line 1
#define state_double_back 2
#define PI 3.1415926535897932384626433832795
Beep_c Buzzer;
Robot_actions_c Actions;
Motors_c Motors;

Kinematics_c Kin;

PID_c Left_PID;
PID_c Right_PID;
PID_c Home_dist_PID;
PID_c Home_angle_PID;

LineSensor_c Sensors;

int state = state_find_line;
int lost_line = 0;
bool double_backed = true;

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


  float old_theta = 0;
void loop() {
  
    Kin.update();
    Sensors.white_calibration();
    Sensors.update_readings(); 
    Motors.update_motors();   
    
  if (abs(PI-(Kin.theta-old_theta)) > 0.03*PI ) {
    Home_angle_PID.K_p = 1;
    Home_angle_PID.K_i = 0;
    Home_angle_PID.K_d = 0;
    Home_angle_PID.demand = PI;
    Home_angle_PID.demand = Home_angle_PID.demand;
    Home_angle_PID.value = Kin.theta;
    Home_angle_PID.calculate_command();
    


    Left_PID.demand = 0.7*Home_angle_PID.command;
    Right_PID.demand = -0.7*Home_angle_PID.command;

    Serial.print(Left_PID.command);
    Serial.print(",");
    Serial.print(Left_PID.demand);
    Serial.print(",");
    Serial.print(Home_angle_PID.value);
    Serial.print(",");
    Serial.println(Home_angle_PID.demand);
    
    Left_PID.K_p = 25;
    Left_PID.K_i = 0.002;
    Left_PID.K_d = 10;
    
    Left_PID.value = Kin.Ang_speed_e1;
    Left_PID.calculate_command();
    Motors.L_speedo = Left_PID.command;

    /*
    Serial.print(Left_PID.value);
    Serial.print(",");
    Serial.println(Left_PID.demand);
*/

    Right_PID.K_p = 25;
    Right_PID.K_i = 0.002;
    Right_PID.K_d = 10;
    
    Right_PID.value = Kin.Ang_speed_e0;
    Right_PID.calculate_command();
    Motors.R_speedo = Right_PID.command;
  }
  else{
    Left_PID.demand = 0;
    Right_PID.demand = 0;
    Motors.R_speedo = 0;
    Motors.L_speedo = 0;
  }

/*
    Home_dist_PID.K_p = 40;
    Home_dist_PID.K_i = 0;
    Home_dist_PID.K_d = 10;
    Home_dist_PID.demand = 1000.0;
    Home_dist_PID.demand = 0.95*Home_dist_PID.demand;
    Home_dist_PID.value = sqrt(pow(Kin.X,2)+pow(Kin.Y,2));
    Home_dist_PID.calculate_command();
    
    Serial.print(Home_dist_PID.value);
    Serial.print(",");
    Serial.println(Home_dist_PID.demand);
*/
    


  

  } 
