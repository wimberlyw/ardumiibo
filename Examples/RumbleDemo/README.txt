

\\Note, Tones don't work with the Project ABE emulator\\


The Rumble Features works off the BeepPin2 from the tones library in Arduboy2. So basically all you need to do is 
Before setup
Make an instance of BeepPin2, then call it like a normal tone. 

BeepPin2 rumble; // Rumble motor runs on Speaker Pin 2

void setup() {
 rumble.begin();//Set up Rumble Motor 
}
  
	 if (arduboy.justPressed(B_BUTTON)) {

	rumble.tone(beep.freq(523.251), 5); /beep.freq(523.251) is used to convert 523.251Hz to the required count
	}


It's that easy. 