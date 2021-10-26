// this #ifndef stops this file
// from being included mored than
// once by the compiler. 

#ifndef _ROBOT_ACTIONS_H
#define _ROBOT_ACTIONS_H

class Robot_actions_c {
  public:
  
    #include "motors.h"
    Motors_c Motors;

    
    void go_straight() {
      
        Motors.L_speedo = 50+ (count_e0-count_e1)*3;
        Motors.R_speedo = 50+ (count_e1-count_e0)*3;
      
        Motors.update_motors();
        
    }

};



#endif
