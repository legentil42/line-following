#define BAUD_RATE 9600

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


// Pin definitions, to make the
// code easier to read.
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
byte l_power;
byte r_power;


// the setup function runs once when you press reset or power the board
void setup() {
  // Set our motor driver pins as outputs.
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );

  // Set initial direction for l and r
  // Which of these is foward, or backward?
  digitalWrite( L_DIR_PIN, LOW  );
  digitalWrite( R_DIR_PIN, HIGH );

  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

  
  //Start a serial connection
  Serial.begin(BAUD_RATE);
  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");
  //play sound:
  buzz(1400,500);
  buzz(1000,500);




}

void loop() {
  // put your main code here, to run repeatedly:

  // Adjust power. e.g., increment by 4 on every loop()
  l_power = l_power + 4;
  r_power = r_power + 4;

  // Send power PWM to pins, to motor drivers.
  analogWrite( L_PWM_PIN, l_power );
  analogWrite( R_PWM_PIN, r_power );

  // Brief pause
  delay(250);

}
