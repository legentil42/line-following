unsigned long TT_duree;  
unsigned long TT_pitch;
bool OnOrOff = true;

int D=3405;
int Ds=3214;
int E=3033;
int F=2863;
int Fs=2702;
int G=2551;
int Gs=2407;
int A=2272;
int As=2145;
int B=2024;
int Cp=1911;
int Cps=1803;
int Dp=1702;




/* sweat dreams
int notes[14]={F,F,D,F,F,E,F,F,F,D,F,G,F,E};
int temps[14]={4,4,4,8,4,2,8,4,4,4,8,4,8,4};
*/

/* all star */
int notes[23]={G,Dp,B,B,A,G,G,Cp,B,B,A,A,G,G,Dp,B,B,A,A,G,G,E,D};
int temps[23]={4,8,8,4,8,8,8,4,8,8,8,8,4,8,8,8,8,8,8,8,8,4,4};

// Remember: Setup only runs once when the arduino is powered up.
void setup() {


   pinMode(6, OUTPUT );



    for (int thisNote = 0; thisNote < 23; thisNote++) {
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
