
#include <Arduboy2.h>


// make an instance of arduboy used for many functions
Arduboy2 arduboy;

// ------------Rumble and sound
BeepPin1 beep; // Create a class instance for speaker pin 1
BeepPin2 rumble; // Rumble motor runs on Speaker Pin 2


// Menu Positions and such
byte alignX = 5;
byte cursorY = (7/2)-1;
byte cursorX = 0;
byte menuItem =1;
byte maxMenu =2;
byte minMenu =1;

void playerInput(){
    arduboy.pollButtons();

   if (arduboy.justPressed(DOWN_BUTTON) && menuItem<maxMenu) {
    cursorY+=11;
    menuItem++;
   }

   if (arduboy.justPressed(UP_BUTTON) && menuItem>minMenu) {
    cursorY-=11;
    menuItem--;
   }
   
   if (arduboy.justPressed(B_BUTTON)) {
      if (menuItem==1){
//---------------------------------------This is where the Tone Happens---------------------------------//
      //Play a 523.251Hz tone (piano note C5) for 5 frames (200ms at 25 FPS)
      beep.tone(beep.freq(523.251), 5);
      }
//---------------------------------------This is where the Rumble Happens---------------------------------//
      if (menuItem==2){
      //beep.freq(523.251) is used to convert 523.251Hz to the required count
      rumble.tone(beep.freq(523.251), 5);
   
      } 
    
      
    }
}
void drawMenu(){
 
   arduboy.setCursor(alignX, 0);
   arduboy.print(F("Tone"));
   arduboy.setCursor(alignX, 11);
   arduboy.print(F("Rumble"));
  //the cursor is a roundRect
   arduboy.fillRoundRect(cursorX, cursorY, 4, 4, 1);
  

  // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();}

  
 void setup() {
  // initiate arduboy instance
  arduboy.begin();
  // here we set the framerate to 25, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(25);


 //Rumble and audio
 arduboy.audio.on();
 beep.begin(); // Set up the hardware for playing tones
 rumble.begin();//Set up Rumble Motor    
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  beep.timer(); // handle tone duration each loop
  rumble.timer(); //handle rumble duration each loop

  playerInput();
  arduboy.clear();
  drawMenu();
  

}
