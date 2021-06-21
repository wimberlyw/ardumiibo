#include "characters.h"


PlayerOne::PlayerOne()
{
      this->posY = 0;
      this->posX = 0;
      this->shield = 0;
      this->animStep = 0;
      this->canJump = false;    
}

// CHANGE THIS TO BE PULLED FROM MENU VALUES
const uint8_t PROGMEM *PlayerOne::getSpriteSet(String charName)
//const uint8_t PROGMEM *PlayerOne::getSpriteSet()
{
  if(charName == "Beefball"){
    return beefball;
    
  }else if(charName == "Runner"){
    return runningman;
    
  }else if(charName == "C-Cube"){
    return companion;
    
  }else if(charName == "Dino"){
    return dino;
  
  }else{
    return runningman;
  }
}
