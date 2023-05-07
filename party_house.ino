#include "pitches.h"
#include "songs.h"

#define BUTTON_PIN 8
#define SPEAKER_PIN 7
bool Status=false;

int RED = 9;
int GREEN = 10;
int BLUE = 11;

/* set up function */
void setup() {

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // enable input/output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  // seed random() function so that we get a different order
  randomSeed(analogRead(0));
}



/* main while loop function */
void loop() {
        //  RGB_color(255, 255, 0); 
        // delay(300);
        RGB_color(0, 255, 255);
        delay(300);
        RGB_color(255, 0, 0);
        delay(300);



  // check to see if button is pressed
  // if (digitalRead(BUTTON_PIN) == HIGH) {
  //   // delay 50 ms to make sure it's still pressed
  //   // avoids any stray misreadings

  // //   //delay(50);
    if(digitalRead(BUTTON_PIN) == HIGH) {
          
      // randomly choose a song
      int song_choice = random(3);
        
      // select which song to play
      switch (song_choice) {
        case 0:
        play_song(marioLength,mario,marioDurations,marioTempo);
          break;
         case 1:
           play_song(hpLength,hp,hpDurations,hpTempo);
           break;
         case 2:
           play_song(keyboardcatlength,keyboardcat,keyboardcatDurations,keyboardcatTempo);
           break;
          //  case 3:
          //  play_song();
          //  break;
          //  case 4:
          //  play_song();
          //  break;
          //  case 5:
          //  play_song();
          //  break;
      }
    }

        RGB_color(255, 0, 0); 
        delay(300);
        RGB_color(0, 255, 0);
        delay(300);
        // RGB_color(0, 0, 255); 
        // delay(300);
        // RGB_color(255, 0, 255);
        // delay_(300);
}
//}
/* plays the song */
void play_song(int num_notes, int melody[], int noteDurations[], int tempo) {
 
  Status=true;

  for (int i=0; i<num_notes; i++) {
    int duration = 0;
    // calculate the duration of each note
    if (noteDurations[i] > 0) {
      duration = tempo / noteDurations[i];
    }
    // if it's a negative number, means dotted note
    // increases the duration by half for dotted notes
    else if (noteDurations[i] < 0) {
      duration = tempo / abs(noteDurations[i]) * 1.5;
    }
    tone(SPEAKER_PIN, melody[i], duration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);

     int pin_color = random(7);
  switch (pin_color) {

        case 0:
        RGB_color(255, 0, 0); 
        break;

         case 1:    
        RGB_color(0, 255, 0);
        break;

        case 2:
        RGB_color(0, 0, 255); 
        break;

        case 3:
        RGB_color(255, 0, 255);
        break;

         case 4:    
        RGB_color(255, 255, 0); 
           break;

        case 5:
        RGB_color(0, 255, 255);
           break; 
      
        default:
        RGB_color(255, 0, 0);
        break;

      }  
    
  }
  Status=false;

  

}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(RED, 255-red_light_value);
  analogWrite(GREEN, 255-green_light_value);
  analogWrite(BLUE, 255-blue_light_value);
  }
