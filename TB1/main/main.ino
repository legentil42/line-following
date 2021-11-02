
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
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
#define PI 3.1415926535897932384626433832795
Beep_c Buzzer;
Robot_actions_c Actions;
Motors_c Motors;
Kinematics_c Kin;

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

  unsigned long t0 = millis();
  while (millis()-t0 < 5000){
    Kin.update();
  }
  Buzzer.buzz(1911,100);
  float theta_1 = atan2(Kin.Y,Kin.X);
  float dist_to_home = sqrt(pow(Kin.X,2)+pow(Kin.Y,2));
  Actions.turn_theta_rad(PI+theta_1);
  delay(200);
  Kin.theta = Kin.theta + PI;
  Kin.update();
  
  Actions.reset_count();
  float min_dist = sqrt(sq(Kin.X)+sq(Kin.Y));
  while(min_dist <= sqrt(sq(Kin.X)+sq(Kin.Y))){
      
      Serial.print(min_dist);
      Serial.print(" ,");
      Serial.println(sqrt(sq(Kin.X)+sq(Kin.Y)));
      if (min_dist >= sqrt(sq(Kin.X)+sq(Kin.Y))) {
        min_dist = sqrt(sq(Kin.X)+sq(Kin.Y));
      }
      else {break;}
      Kin.update();
      Actions.go_straight();
  }
          Motors.L_speedo = 0;
        Motors.R_speedo = 0;
      
        Motors.update_motors();
}



void loop() {






  
/*
    Serial.print(state);
    Serial.println(",");
  if (state == state_find_line) {
      Actions.go_straight();   
      if (Actions.check_for_line() == true) {
        state = state_follow_line;
        
      }
      if (double_backed == false && millis()-Actions.lost_line_time >1000) {
        Actions.turn_on_spot();
        double_backed = true;
      }
  }
  
  if (state == state_follow_line) {
    Actions.follow_line();
    
    if (Actions.check_for_line() == false) {
        state = state_find_line;
        Actions.reset_count();
        double_backed = false;
      }
      
  }
  
  
  if (state == state_double_back) {
    Actions.turn_theta_degrees(180);
    if (Actions.check_for_line() == true) {
        state = state_follow_line;

      }
  }
      
    
    */
    
  } 
