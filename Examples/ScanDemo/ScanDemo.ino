
#include <Arduboy2.h>
#include "sprites.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

//   ---------------------- Menu positions and such
byte UIX = WIDTH - 36;
bool scanON;
int heartsEarned =2;
int heartsMax = 3;
int characterX = 32;
int characterY = HEIGHT - 32;
bool facingLeft = true;
bool hasKey = false;
int spriteFrame = 0;

//-------------------------------RFID Scanner Variables
String Message;//Storing messages from the scanner as a string here. 

// ------------Set your secret code you want to read from the RFID.
// The  "codes" we will be scanning for. 
// i.e a character name or whatever you want to write to your rfid tags to read here.  
// All the writers write with the word "en" in front 
// so you have to include en in front, 
// Or skip the first 3 chars if comparing the string. 
// This example skips the first 3 chars

String keyCode = "keys"; 
String  potionCode = "pots";

 
// first character is an initialize, you just can't see it. 
// Some other weird stuff we found was that if you're comparing strings, 
// Serial1.readString will add an invisible \r to the end of the string, 
// so watch that if you compare the string directly. 

//   ---------------  This code is activated when you try to read the door. So if you DONT want to just scan whenever, but on a certain event instead, do this. 
void scanFromMenu(){
  if(!scanON){arduboy.display();}

  else{
 // -------------------------------------------Blocking Scan Loop-------------------
 //This loop is blocking so we only start it when scanON is true. 
 
     arduboy.setCursor(4,9);
     arduboy.print("Scan a key to enter");
     arduboy.display();
     //read 
      //if(Serial1.available())  //WE COMMENT OUT THIS LINE HERE SO IT WILL BLOCK THINGS UNTIL YOU SCAN WHAT IT WANTS. We uncomment it in the scan anytime function. 
     {Message = Serial1.readString();} //Store String received in Message

     //
     //Check to see if your secret code (in this case the code for the Key) is contasined in the Message we received from Serial1
     //
     //
     if(Message.indexOf(keyCode) >= 0){   //Search the message for our code, set in setup
         arduboy.clear();
         //----------------This is where your reaction to scanning a match goes. 
         //Mine sets a global variable to display a key, 
         // and also Brings up a big painted rectangle that confirms you've scanned the right stuff. 
         //currentlty this will block until you DO scan the right stuff.
         //
         hasKey= true; 
         arduboy.fillRect(0,0,WIDTH, HEIGHT, WHITE);
         arduboy.fillRect(4,4,WIDTH-8, HEIGHT-8, BLACK);
         arduboy.setCursor((WIDTH/2)-30, (HEIGHT/2)-7);
         arduboy.print("Key Scanned!");
         arduboy.display();
         arduboy.delayShort(2500);
         scanON = false;  //this just pops me out of my loop and back to the menu next go around. 
         
          //Serial1.end();  //   You could end the serial connection and disable the power to serial if you wanted to after one scan. You could probably turn it back on...not sure
          //power_usart1_disable();
       
      
     } 
     //Could cancel a scan if you spam it
       if (arduboy.pressed(B_BUTTON)) {
        scanON = false;
        
      }
  }
}

// ----------------------For Scanning anytime  NONBLOCKING ----------------------
void scanAnytime(){
   if(Serial1.available()){  //THIS LINE MAKES SERIAL NOT LOCK UP EVERYTHING BY SCANNING ALL THE TIME, BUT ONLY WHEN DATA COMES
   Message = Serial1.readStringUntil('\r');     //Store incoming data
   
   if(Message != ""){    
        
        //We've found that the writer apps put an extra " en/" in the string, so we take it out. 
        Message.remove(0,3);
                
                          
        // if it exists, do stuff.
          if(Message.indexOf(potionCode) >= 0){      //if our code exists in what was scanned
                                    //do stuff
            Serial1.flush();   //Clear the serial buffer of any info
            arduboy.delayShort(1000);    //add a lil delay time
            heartsEarned++; 
           }

           if(Message.indexOf(keyCode) >=0){
            Serial1.flush();   
            arduboy.delayShort(1000);
            hasKey =true;
            
           }
        }   
    }
}

void playerInput(){
  arduboy.pollButtons();
  if (arduboy.pressed(LEFT_BUTTON) && characterX>0) {characterX-=1, spriteFrame++; facingLeft = true;}
  if (arduboy.pressed(RIGHT_BUTTON) && characterX + 32< WIDTH-16) {characterX+=1,spriteFrame++; facingLeft=false;}
  if (arduboy.justPressed(B_BUTTON) && heartsEarned>=0) {heartsEarned--;} 

  if(arduboy.justPressed(A_BUTTON) && characterX == WIDTH-48){
    arduboy.clear();
    scanON = true; // ------------Enter the loop to Scan things;}
    
  }
  
}

void drawui(){
  // -------------------Draw the Hearts
  arduboy.fillRect(UIX, 0, 48, 8, BLACK);
  arduboy.setCursor(UIX, 0);
  arduboy.print("[");
  arduboy.setCursor(UIX+30,0);
  arduboy.print("]");
  (heartsEarned>heartsMax)&&(heartsEarned=heartsMax);
  for( int k =0; k<heartsEarned; k++ ){Sprites::drawOverwrite((k*9)+UIX+5, 0, heart, 0);}
  //-------------------Draw the Key
  arduboy.fillRect(UIX, 10, 48, 8, BLACK);
  arduboy.setCursor(UIX, 10);
  arduboy.print("[");
  if(hasKey){Sprites::drawOverwrite(9+UIX+5, 10, key, 1);}
  else{Sprites::drawOverwrite(9+UIX+5, 10, key, 0);}
  arduboy.setCursor(UIX+30,10);
  arduboy.print("]");
  Sprites::drawOverwrite(UIX + 16, HEIGHT -16, doa, 0);
  scanFromMenu();

}
void drawCharacter(){
  if(spriteFrame>5){spriteFrame=0;}
  if(facingLeft){Sprites::drawOverwrite(characterX, characterY, GL0, spriteFrame);}
  else{Sprites::drawOverwrite(characterX, characterY, GR0, spriteFrame);}
  
}


void setup() {
  // initiate arduboy instance

  // here we set the framerate to 30, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.begin();
  arduboy.setFrameRate(30);


 
 scanON = false; //dont start in scanning mode until you enter the scan option on the menu
 arduboy.audio.off();

 power_usart1_enable(); // Arduboy turns off serial power, so we need that to connect to the RFID reader
 Serial1.begin(115200);// Begin communication with the Serial port/ Reader over Serial 1
        
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  playerInput();
  arduboy.clear();
  drawCharacter();
  drawui();
  scanAnytime();
 
}
