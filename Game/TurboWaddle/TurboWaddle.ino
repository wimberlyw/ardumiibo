
//MAKE SURE TO SCAN FOR DEBUG

#include <Arduboy2.h>
//#include <ArduboyTones.h>
#include "characters.h"
#include "menus.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
BeepPin1 beep; // Create a class instance for speaker pin 1
BeepPin2 rumble; // For speaker pin 2, use this line instead of the line above

//ArduboyTones noise(arduboy.audio.enabled);

short spawnTimer;
short spawnDelay;
short topBarSize;
short groundBarPos;
short score;
short gameState;
short gameSpeed;
float gravity;
bool firstStep;

// CHARACTER UNLOCKS
String CharacterNames[] = {"Runner" , "Beefball", "Dino" , "C-Cube"};
bool CharacterUnlocks[] = {true     , false     , false  , false    };


struct Enemy {

  int posX, posY;
  int sizeBox;
  bool isAlive;
};



const int arSize = 8;
Enemy enemyPixel[arSize];
int backgroundLines[arSize];

PlayerOne player;
Menus gameMenu;


//####################################################
//################### START OF CODE ##################
void setup() {
  arduboy.begin();
  
  arduboy.setFrameRate(30);
  arduboy.audio.on();

//-----TURN ON SERIAL-----
  power_usart1_enable();
  Serial1.begin(115200);

//-----TURN ON RUMBLE-----
beep.begin(); // Set up the hardware for playing tones
rumble.begin();//Set up Rumble Motor

  //creates the lines and values to use for the ground or it looks weird on startup
  for (int i = 0; i < arSize; i++) {
    backgroundLines[i] = i * (arduboy.width() / arSize);
  }

  gameState = 0;
  gameSpeed = 2;
  player.animStep = 0;
  firstStep = true;

}

// ++++ game begin +++++
void loop() {
  if (!(arduboy.nextFrame()))
    return;
  beep.timer(); // handle tone duration
  rumble.timer(); //handle rumble duration
  arduboy.pollButtons();
  arduboy.clear();

  //------------------- START MENU ---------------------------------------
  if (gameState == 0) {
    // DO STUFF HERE FIRST
    if (firstStep) {
      groundBarPos = 65;
      gameMenu.ResetMenuStates();
      firstStep = false;
    }

    drawGround(groundBarPos);

    //lower intro title
    if (arduboy.everyXFrames(5)) {
      gameMenu.animStep = (gameMenu.animStep + 1) % 2;
    }

    if (groundBarPos <= 50)
    {
      short menuX = gameMenu.menuState > 0 ? -pow(gameMenu.animStepAlt - 4, 2) + 16 : 0; //fancy animation :D

      gameMenu.drawMenuTitle(32 + menuX, 0);

      // flash start selection
      if ((millis() % 1000) < 500) {
        gameMenu.Start(arduboy, 26 + menuX, 40); //flash the start button
      }
      //if not animating
      if (arduboy.everyXFrames(2) && gameMenu.menuState > 0)
      {
        gameMenu.animStepAlt++;
        if (gameMenu.animStepAlt > 15)
        { // when title is done change menu to charSelect
          gameState = 2;//the actual swap
        }
      }

      if ((arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) && gameMenu.menuState == 0)
      {
        gameMenu.menuState++;
      }
    } else {
      //this allows you to skip intro animation
      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
        groundBarPos = 50;
      }

      short titlePosY = -32 * (groundBarPos - 50) / 14; //calculate top down anim
      gameMenu.drawMenuTitle(32, titlePosY);

      if (arduboy.everyXFrames(3)) {
        groundBarPos--;
      }

    }

    //end of menu
    if (gameState != 0) {
      firstStep = true;
      gameMenu.ResetMenuStates();
    }
    arduboy.display();
  }
  //------------------- CHARACTER SELECT ---------------------------------
  else if (gameState == 2) {
    if (firstStep) {
      groundBarPos = 50;
      gameMenu.ResetMenuStates();
      firstStep = false;
    }
    drawGround(groundBarPos);

    gameMenu.CharacterSelect(arduboy, CharacterNames, CharacterUnlocks, 0, 0);

    //NEEDS TO SWOOS RIGHT IN
    // FIX IT

    if (arduboy.justPressed(B_BUTTON)) {
      if ( gameMenu.select < 4) {
        if (CharacterUnlocks[gameMenu.select]) 
        {
          player.selectedChar = CharacterNames[gameMenu.select];
          gameState = 1;//Change to main game loop
        }
      } else if (gameMenu.select == 4) {
        gameState = 3;//change to Scan menu
      }

    } else if (arduboy.justPressed(A_BUTTON)) {
      gameState = 0;
    }

    //if exiting the current gameState, reset.
    if (gameState != 2) {
      firstStep = true;
    }
    arduboy.display();
  }
  //------------------- SCAN MENU ----------------------------------------
  else if (gameState == 3) {
    if (firstStep) {
      groundBarPos = 50;
      gameMenu.ResetMenuStates();
      firstStep = false;
      gameMenu.menuState = -1;
    }
    
    gameMenu.ScanMenu(arduboy, CharacterNames, CharacterUnlocks, 0, 0);
    if(gameMenu.menuState == 7){
      gameState = 2;
      firstStep = true;
    }

    arduboy.display();
  }
  //------------------- MAIN GAME ----------------------------------------
  else if (gameState == 1) {
    //--------------------------------------------------------------------
    // --------Here is where you initialize the game, not in setup--------
    if (firstStep) {
      spawnTimer = 0;
      spawnDelay = 33; // time between spawns editable (33 = 1sec)
      topBarSize = 8;
      groundBarPos = 50;
      score = 0;
      gravity = 0;
      randomSeed(millis()%9999);

      player.posY = groundBarPos - 16;
      player.posX = 24;
      player.shield = 50;
      player.canJump = false;
      //player.selectedChar = "dino";



      for (int i = 0; i < arSize; i++)
      {
        enemyPixel[i].sizeBox = 5;
        enemyPixel[i].posX = 130;
        enemyPixel[i].posY = 32;
        enemyPixel[i].isAlive = false;
      }

      firstStep = false;
    }
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------

    drawGround(groundBarPos);

    // PLAYER JUMP CONTROL
    int jumpOffset = groundBarPos; //where the chracters actual ground is

    if ((arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) && player.canJump) {
      gravity = 5;
      player.canJump = false;
      player.posY = jumpOffset - 1;
    }
    else if (player.posY < jumpOffset) {
      //if player is not on ground
      player.posY = player.posY - (int)gravity;
      gravity = gravity - 0.5f;

      //alternative to math.clamp()
      if (player.posY > jumpOffset) {
        player.posY = jumpOffset;
      }
    }
    else { //set player to ground and stop movement
      gravity = 0;
      player.canJump = true;
    }


// ------------- ENEMY CONTROLS ----------------

    for (int i = 0; i < arSize; i++) {

      if (enemyPixel[i].isAlive == true) { //ENEMY DRAW LOOP
        if (enemyPixel[i].posX > (0 - enemyPixel[i].sizeBox)) { // if enemy is on screen
          arduboy.fillCircle(enemyPixel[i].posX, enemyPixel[i].posY, enemyPixel[i].sizeBox, BLACK); // DRAW CALL
          arduboy.drawCircle(enemyPixel[i].posX, enemyPixel[i].posY, enemyPixel[i].sizeBox, WHITE); // DRAW CALL

          enemyPixel[i].posX = enemyPixel[i].posX - gameSpeed;//DRAW CALL

          int distX = enemyPixel[i].posX - player.posX;
          int distY = enemyPixel[i].posY - player.posY;


// ------ COLLISION / DAMAGE CHECK ------
          if ( (abs(distX) < (enemyPixel[i].sizeBox * 2) ) && ( abs(distY) < (enemyPixel[i].sizeBox * 2) ))
          {
            enemyPixel[i].isAlive = false;            
            player.shield = player.shield - 10;

            //-------- DAMAGE EFFECTS GO HERE --------- //they will happen ONCE when you get hit.

            beep.tone(beep.freq(523.251), 10);
            rumble.tone(beep.freq(523.251), 10);
            //--------------------------------------------  
            
            //go to another state if your health is 0
            beep.tone(beep.freq(523.251), 10);
            rumble.tone(beep.freq(523.251), 10);
            arduboy.invert(true);
            delay(75);
            arduboy.invert(false);
          }
        } else {
          enemyPixel[i].isAlive = false; //kill enemy if its off screen
        }
      } else {
        if (spawnTimer >= spawnDelay) {
          //enemyPixel[i].size = 4;
          enemyPixel[i].posX = 128 + enemyPixel[i].sizeBox * 2;
          enemyPixel[i].posY = (groundBarPos - enemyPixel[i].sizeBox * 2 + 12); // REMOVE THE 50
          enemyPixel[i].isAlive = true;

          if (score > 2000) {
            gameSpeed = 6;
            spawnDelay = 25 - random(0, 8);
            enemyPixel[i].posY = enemyPixel[i].posY - (random(0, 2) == 0 ? 20 : 0);
          } else if (score > 1500) {
            gameSpeed = 5;
            spawnDelay = 33 - random(0, 13);
            enemyPixel[i].posY = enemyPixel[i].posY - (random(0, 2) == 0 ? 20 : 0);

          } else if (score > 1000) {
            gameSpeed = 4;
            spawnDelay = 33 - random(0, 10);
            enemyPixel[i].posY = enemyPixel[i].posY - (random(0, 3) == 0 ? 20 : 0);

          } else if (score > 750) {
            spawnDelay = 44 - random(0, 15);
            enemyPixel[i].posY = enemyPixel[i].posY - (random(0, 3) == 0 ? 20 : 0);

          } else if (score > 500) {
            gameSpeed = 3;
            spawnDelay = 55 - random(0, 20);
            enemyPixel[i].posY = enemyPixel[i].posY - (random(0, 4) == 0 ? 20 : 0);

          } else if (score > 0) {
            gameSpeed = 2;
            spawnDelay = 66 - random(0, 33);
          }

          spawnTimer = 0;

        }
      }
    }


    score = score + 1;

// DRAW CALLS
    displayAll();
    arduboy.display();

    if (player.shield <= 0) {
      screenFlash(4, 250);
      gameState = 0;
      gameSpeed = 2;
      firstStep = true;
    }

    if (spawnTimer < spawnDelay) {
      spawnTimer++;
    } //SPAWN COUNTER
  }

}
// END OF GAME

//#######################################################################################
//#################################### FUNCTIONS ########################################
void displayAll() {
  drawShieldBar(1, topBarSize - 7, player.shield);
  drawTopBar(topBarSize);
  //drawGround(groundBarPos);
  drawScore(77, topBarSize - 8, score);
  drawPlayer(player.posY, player.posX);
}

void drawTopBar (int posY) {

  arduboy.drawFastHLine(0, posY, 128, WHITE);

} // Draws the top score bar

void drawGround (int posY) {

  //arduboy.drawFastHLine(0, posY, 128, WHITE);

  int botY = arduboy.height();
  for (int i = 0; i < arSize; i++) {

    //dots inbetween. Same positions as the lines, but shifted by half the amount
    arduboy.drawPixel(backgroundLines[i] + ((arduboy.width() / arSize) / 2), posY);

    backgroundLines[i] -= gameSpeed / 2;
    if (backgroundLines[i] < 0) {
      backgroundLines[i] = arduboy.width();
    }


    int topPos = backgroundLines[i] + (2 * backgroundLines[i] - arduboy.width());
    arduboy.drawLine(backgroundLines[i], posY, topPos, botY);
  }
}

//Draws a triagle represented by the player
void drawPlayer(int yPos, int xPos) {

  if (player.canJump) {
    int frameskip = 5 - gameSpeed;
    if (frameskip < 1) {
      frameskip = 1;
    }
    if (arduboy.everyXFrames(frameskip)) {
      player.animStep = (player.animStep + 1) % 4;
    }
  } else {
    player.animStep = 4;
  }

  // -8 for the offset of the 16x16 sprite
  Sprites::drawSelfMasked(xPos - 8, yPos - 8, player.getSpriteSet(player.selectedChar), player.animStep);
}

void drawShieldBar(int posX, int posY, int shield) {
  int spacing = 4;
  int width = 50;

  int originX = posX + width + spacing * 2 - 2;
  int originY = posY + 2;
  int scale = 1;

  //BAR
  arduboy.drawRoundRect(posX, posY, width, 5, 2, WHITE);
  if (shield > 20 ) {
    arduboy.fillRoundRect(posX, posY, shield, 5, 2, WHITE);
  }
  else if (shield > 10) {
    if ((millis() % 500) > 250) {
      arduboy.fillRoundRect(posX, posY, shield, 5, 2, WHITE);
    }
  }
  else if (shield > 0) {
    if ((millis() % 250) > 125) {
      arduboy.fillRoundRect(posX, posY, shield, 5, 2, WHITE);
    }
  }

  //SYMBOL
  arduboy.drawChar(posX + width + spacing * 0, posY - 1, '(', WHITE, BLACK, 1);
  arduboy.drawChar(posX + width + spacing * 2, posY - 1, ')', WHITE, BLACK, 1);

  int tip1x = originX + (3 * scale);
  int tip1y = originY;

  int tip2x = originX - (2 * scale);
  int tip2y = originY + (2 * scale);

  int tip3x = originX - (2 * scale);
  int tip3y = originY - (2 * scale);
  arduboy.drawTriangle(tip1x, tip1y, tip2x, tip2y, tip3x, tip3y, WHITE);
} // Draws the shield bar for health

void drawScore(int posX, int posY, int score) {

  arduboy.setCursor(posX, posY);
  arduboy.print("sc:" + String(score));

} // draw and handle score

void screenFlash(int flashAmount, short flashTime) {
  int t = flashAmount * 2 + 1;
  for (int i = 0; i < t; i++) {
    arduboy.invert(i % 2);
    delay(flashTime);
  }
}
