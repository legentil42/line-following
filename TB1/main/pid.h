// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _PID_H
#define _PID_H

// Class to contain generic PID algorithm.
class PID_c {
  public:
  
    // Constructor, must exist.
    PID_c() {
        float demand;
        float feedback;
        float value;
        float K_p;
        float K_i;
        float K_d;
        float command;
    }

    void calculate_command() {
      feedback = demand - value;
      command = K_p * feedback;

    }

};



#endif
