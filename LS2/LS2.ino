#define BAUD_RATE 9600
// Pin definitions, to make the
// code easier to read.
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

#define FORWARD 0
#define BACKWARD 1


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


// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
byte l_power;
byte r_power;
float speedo = 0;
int actual_step = 0;

//variable for time managment
unsigned long Timer1 = millis();
unsigned long Timer2 = millis();
unsigned long Timer3 = millis();
unsigned long Timer4 = millis();
unsigned long current_time = millis();
int more_or_less = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // Set our motor driver pins as outputs.
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );



  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

  
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");
  //play sound:
  //buzz(1276,200);
  //buzz(1517,200);
  //buzz(1911,100);
  buzz(1517,100);
  buzz(1276,100);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = millis();
  
  if (current_time-Timer1 > 2000) {
    
            
            L_go(100);
            R_go(100);
            delay(2000);
            L_go(0);
            R_go(0);           
            Timer1 = millis();
    
  }
  
}
