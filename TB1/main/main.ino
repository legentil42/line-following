
#include "beep.h"
#include "motors.h"
#include "encoders.h"
#include "robot_actions.h"
#define BAUD_RATE 9600
#define state_find_line 0
#define state_follow_line 1

Beep_c Buzzer;
Robot_actions_c Actions;
//Motors_c Motors;
int state = state_find_line;

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



void loop() {
 
   
  if (state == state_find_line) {
      Actions.go_straight();      
      if (Actions.check_for_line() == true) {
        state = state_follow_line;
      }
      
  }
  
  if (state == state_follow_line) {
    Actions.follow_line();
  }
  

  // Print output.

    
    
    
  }
