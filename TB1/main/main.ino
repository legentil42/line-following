
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "robot_actions.h"
#define BAUD_RATE 9600
#define state_find_line 0
#define state_follow_line 1
#define state_double_back 2
#include "pid.h"
#include "linesensor.h"
#define BAUD_RATE 9600
#define state_find_line 0
#define state_follow_line 1
#define state_double_back 2
#define go_home 3
#define finished 4
#define PI 3.1415926535897932384626433832795
Beep_c Buzzer;
Robot_actions_c Actions;
Motors_c Motors;


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

}
float last_theta = 0;
int state = state_find_line;
int lost_line = 0;
bool double_backed = true;
unsigned long time_lost_line = millis();
float X_limit = 450;
float new_theta;
void loop() {
  /*
  while (last_theta > 2*PI) {
    last_theta = last_theta - (2*PI);

  }*/
    Actions.Kin.update();

    if (state == state_find_line) {
      
      Actions.go_straight(last_theta);
      
      if (Actions.check_for_line() == true) {
        state = state_follow_line;
      }

      if (double_backed == false && millis()-time_lost_line > 750 && Actions.Kin.X < X_limit) {

        new_theta = Actions.turn_theta_rad(last_theta+PI);

        last_theta = new_theta;
        double_backed = true;
      }

      if (Actions.Kin.X > X_limit) {
        Motors.L_speedo = 0;
        Motors.R_speedo = 0;
        Motors.update_motors();
        state = go_home;
      }
    }

    
    if (state == state_follow_line) {
          Actions.follow_line();

      if (Actions.check_for_line() == false) {
        state = state_find_line;
        last_theta = Actions.Kin.theta;
        time_lost_line = millis();
        double_backed = false;
        Buzzer.buzz(2500,50);
      }
    
    }


    if (state == go_home) {

      //Actions.go_back_home();
       Actions.Kin.update();
        

        delay(1000);
        Buzzer.buzz(1200,100);
        Buzzer.buzz(1000,100);
        Buzzer.buzz(800,100);
        
        float theta_1 = atan2(Actions.Kin.Y,Actions.Kin.X);
        new_theta = Actions.turn_theta_rad(PI+theta_1);
        delay(200);
        Buzzer.buzz(1200,100);
        Buzzer.buzz(1000,100);
        while (Actions.Kin.X >0){
          Actions.go_straight(new_theta);
        }
        Motors.L_speedo = 0;
        Motors.R_speedo = 0;
        Motors.update_motors();
       state = finished;
    }

     
    
   

    if (state == finished) {
      
    Buzzer.buzz(1911,100);
    Buzzer.buzz(1517,200);
    Buzzer.buzz(1911,100);
    }

}
    /*
  if (state == state_find_line) {
      Actions.go_straight(last_theta);   
      if (Actions.check_for_line() == true) {
        state = state_follow_line;
      }
      if (double_backed == false && millis()-Actions.lost_line_time >1000) {
        state = state_double_back;
      }
  }
  
  if (state == state_follow_line) {
    Actions.follow_line();
    
    if (Actions.check_for_line() == false) {
        state = state_find_line;
        Actions.reset_count();
        last_theta = Kin.theta;
        double_backed = false;
      }
      
  }
  
  
  if (state == state_double_back) {
    last_theta = Kin.theta;
    Actions.turn_theta_rad(last_theta+PI);
    last_theta = last_theta+PI;
    Kin.update();
    
    double_backed = true;
    last_theta = Kin.theta;
    state = state_find_line;
     
  }
      */
    
    
  
