#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

#define FORWARD 0
#define BACKWARD 1

#include "linesensor.h"

void L_go (float L_speedo) {

  if (L_speedo < 0){
      // Set initial direction for l
  digitalWrite( L_DIR_PIN, BACKWARD );
  }
  
  else{
      // Set initial direction for l
  digitalWrite( L_DIR_PIN, FORWARD );
  }

  analogWrite( L_PWM_PIN, int(abs(L_speedo)) % 255 );
  
}


void R_go (float R_speedo) {

  if (R_speedo < 0){
      // Set initial direction for l
  digitalWrite( R_DIR_PIN, BACKWARD );
  }
  
  else{
      // Set initial direction for l
  digitalWrite( R_DIR_PIN, FORWARD );
  }

  analogWrite( R_PWM_PIN, int(abs(R_speedo)) % 255);
  
}

#define BAUD_RATE 9600
// Pin definitions, to make the
// code easier to read.

#define EMIT_PIN 11
#define DN2_PIN 18
#define DN3_PIN 20
#define DN4_PIN 21

void buzz (float pitch, int duree) {
pinMode(6, OUTPUT );
unsigned long TT_duree = millis();
unsigned long TT_pitch = micros();
while (millis() - TT_duree < duree) {
  if (micros()-TT_pitch > pitch) {
    digitalWrite(6,!digitalRead(6));
    TT_pitch = micros();
  }
}
digitalWrite(6,0);
delay(duree/8);
}



//variable for time managment
LineSensor_c Sensors;

// the setup function runs once when you press reset or power the board
void setup() {
  // Set our motor driver pins as outputs.

  
  
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");
  //play sound:
  buzz(1276,200);
  buzz(1517,200);
  buzz(1911,100);
  buzz(1517,100);
  buzz(1276,100);
  delay(2000);

}

void loop() {

  Sensors.update_DN2();
  Sensors.update_DN3();
  Sensors.update_DN4();    
  // Print output.
  Serial.print("DN2,3,4: " );
  Serial.print( Sensors.DN2_VALUE);
  Serial.print("," );
  Serial.print( Sensors.DN3_VALUE);
  Serial.print("," );
  Serial.print( Sensors.DN4_VALUE);
  Serial.print("\n");


  if (Sensors.DN2_VALUE > 2000) {
    R_go(80);
    L_go(0);
  }
  else { R_go(0);}
  

    if (Sensors.DN4_VALUE > 2000) {
    L_go(80);
    R_go(0);
  }
   else { L_go(0);}
 

  if (Sensors.DN3_VALUE > 2000) {
    L_go(40);
    R_go(40);
  }
  }
