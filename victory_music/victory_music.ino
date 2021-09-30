unsigned long TT_duree;  
unsigned long TT_pitch;
bool OnOrOff = true;

int D = 1703;
int E = 1517;
int F = 1432;
int G = 1276;




int notes[14]={F,F,D,F,F,E,F,F,F,D,F,G,F,E};
int temps[14]={4,4,4,8,4,2,8,4,4,4,8,4,8,4};
// Remember: Setup only runs once when the arduino is powered up.
void setup() {


   pinMode(6, OUTPUT );



    for (int thisNote = 0; thisNote < 16; thisNote++) {
  int noteDuration = 2000/temps[thisNote];
  buzz(notes[thisNote],noteDuration);
}
}


void buzz (float pitch, int duree) {

TT_duree = millis();
TT_pitch = micros();
while (millis() - TT_duree < duree) {
  

  if (micros()-TT_pitch > pitch) {
    digitalWrite(6,!digitalRead(6));
    TT_pitch = micros();
  
  }

}
digitalWrite(6,0);
delay(duree/8);

}
// Remember: loop is called again and again.
void loop() {



}
