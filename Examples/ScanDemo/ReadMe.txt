


------===================In setup:-==========================
Make sure you have 

 power_usart1_enable(); // Arduboy turns off serial power, so we need that to connect to the RFID reader
 Serial1.begin(115200);// Begin communication with the Serial port/ Reader over Serial 1

You could put the codes you want to scan for in setup as well. Mine are outside, so that they are at the top and can be easily seen. 
	String Message;//Storing messages from the scanner as a string here. 
	
	String keyCode = "keys"; 
	String  potionCode = "pots";




--------------============Some Info About Functions Using Serial-============================

This example basically just reads codes from serial.
There is a blocking and non-blocking way to do it. 


The blocking way doesn't comment out "if(Serial1.available())" 
	which causes it to check non-stop. 

This is good for checking to block the way unless a certain thing is scanned. 



Message = Serial1.readString()  //This is how we store what we receive. 

if(Message.indexOf(YOURCODE) >= 0)  this is how we check to see if our "code" exists ANYWHERE in the Message we received. 


EXAMPLE:

 if(Message.indexOf(potionCode) >= 0) is how I checked in this example if we scanned a key. 



strings are sent over with an invisible '\r' so we use 
	Message = Serial1.readStringUntil('\r'); 

To know when to stop storing the message in the "scan anytime" function. 

Serial1.flush();   //Clears the serial buffer of any info


...................======================== Here are the two functions...............=============================

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
