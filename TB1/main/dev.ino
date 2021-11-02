
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
#include "kinematics.h"
Kin_c Kin;
#include "pid.h"
Pid_c Left_PID;

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



void loop() {

    Kin.update();
    Left_PID.demand = 1;
    Left_PID.value = Kin.Ang_speed_e1;
    Left_PID.calculate_command();
    Motors.L_speedo = Left_PID.command;
    Motors.update_motors();
    
  } 
