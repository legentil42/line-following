
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "robot_actions.h"
#define BAUD_RATE 9600
#define state_find_line 0
#define state_follow_line 1
#define state_double_back 2

Beep_c Buzzer;
Robot_actions_c Actions;
//Motors_c Motors;
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
  Actions.go_X_distance(0);
}



void loop() {
  
    Actions.show_pos();

  /*
    Serial.print(state);
    Serial.print(",");
  if (state == state_find_line) {
      Actions.go_straight();   
      if (Actions.check_for_line() == true) {
        state = state_follow_line;
        
      }
      if (double_backed == false && millis()-Actions.lost_line_time >2500) {
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
    Actions.turn_on_spot();
    if (Actions.check_for_line() == true) {
        state = state_follow_line;

      }
  }

    
    
    */
  } 
