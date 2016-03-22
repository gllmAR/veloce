// need to be compile with arcore lib 
// https://github.com/rkistner/arcore

#define NUMSENSOR 2


int raw[NUMSENSOR];
int cooked[NUMSENSOR];
int lastCooked[NUMSENSOR];
int flag[NUMSENSOR];
int minimum [] = {90,  90}; // set minimum per sensor 
int maximum [] = {512, 512}; // set maximum per sensor




void setup() {}

void loop() {
  // put your setup code here, to run once:
for (int i = 0; i<100; i++){ 
  for (int j = 0; j < NUMSENSOR; j++){
    raw[j] = analogRead(j);
    cooked[j] = (int (constrain (map ( raw[j], minimum[j], maximum[j], 0, 127), 0, 127 )));

      if (cooked[j]!=lastCooked[j]){
        if (cooked[j]==0){ 
         flag[j]++ ;
        }
        lastCooked[j] = cooked[j];
        }
      }
    }
for (int i = 0; i < NUMSENSOR; i++){
if (flag[i]!=0){
  noteOn(0, i, flag[i]);
    flag[i] = 0 ;
     MIDIUSB.flush();
  
  }
 }    
}




void noteOn(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MIDIUSB.write(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDIEvent noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MIDIUSB.write(noteOff);
}
