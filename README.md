# Arduboy Pro Rumble - With Ardumiibo Scanner
### The Arduboy Pro Rumble itself is a homemade Leonardo backpack that has a vibration motor attached to Speaker Pin 2. Game makers can use the Arduboy2 Tones commands to add rumble to their game. The system also features broken out Serial connection to connect the the Ardumiibo Scanner and future peripherals.

### The Ardumiibo scanner is a PN532 NFC Scanner with a Neopixel ring that can scan collectible items from the real world into your game. 

## An Arduboy based nod to Tiger Electronics handhelds, Rumble Features, and [Amiibos](https://www.nintendo.com/amiibo/)


### [Watch The Youtube Playlist Before You Begin](https://youtube.com/playlist?list=PLI37KAai0mUhJ3Yi7gZaNxqZhPj6SuK46)


# TOC

1. [Bill of Materials](https://github.com/wimberlyw/ardumiibo#materials-needed)
2. [Assembly](https://github.com/wimberlyw/ardumiibo#assembly)
    - Arduboy Pro Rumble Game Console
    - Powerboost
    - Boost Cables
    - Scanner
3. [Software](https://github.com/wimberlyw/ardumiibo#software)
4. [Examples](https://github.com/wimberlyw/ardumiibo#load-your-scanner-pro-micro-up-with-the-nfc-reader)  

## Materials Needed:

### Arduboy Pro Rumble:
- Arduino Leonardo
- 10mm x 2.5mm Disc Shape Vibration Motor for Cell Phone - 3v
  - Mine was from uxcel but these look just as good. (https://www.amazon.com/tatoko-12000RPM-Wired-Phone-Vibration/dp/B07L5V5GYG/ref=sr_1_2?dchild=1&keywords=vibration+motor+cell+phone&qid=1624498175&sr=8-2)
 - 2n2222 NPN transistor
 - 3x 110 ohm resistors
 - 10uF 50V capacitor
 - Diode
 - 7x tactile momentary push buttons
 - RGB LED
 - piezo buzzer
 - On off switch
 - 2.42" i2c SSD1309 OLED
 - USB data cable (for booster cable)
 - [3d printer files](https://github.com/wimberlyw/ardumiibo/tree/main/3d%20parts)
 - [Adafruit Powerboost 500](https://www.adafruit.com/product/1944)
    - [Booster cable for Powerboost](https://learn.adafruit.com/booster-cable)
- [3.7V 1200mAh Lipo Battery](https://www.amazon.com/gp/product/B00J2QET64/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)



### Ardumiibo Scanner
-  [3d printer files](https://github.com/wimberlyw/ardumiibo/tree/main/3d%20parts)
-  [24LED Neopixel ring] (https://www.amazon.com/gp/product/B0774JNSCF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
-  [PN532 NFC Reader](https://www.amazon.com/gp/product/B01I1J17LC/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
- USB data cable (for booster cable)
- [Adafruit Powerboost 500](https://www.adafruit.com/product/1944)
- On off switch
- [Booster cable for Powerboost](https://learn.adafruit.com/booster-cable)
- [3.7v 500 mAh Lipo battery](https://www.amazon.com/gp/product/B00L0W61VO/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
- Leonardo Pro Micro
- Perfboard to mount up everything nice 
- NFC stickers for ardumiibos. (https://www.amazon.com/THONSEN-NTAG215-Stickers-Perfectly-NFC-Enabled/dp/B07MKWHYQK/ref=sr_1_5?dchild=1&keywords=rfid+stickers&qid=1624482994&sr=8-5)
- 

## Assembly
  	- Good luck.
  - Add hot glue as wire stress relief as you go. 
  
- Start printing the 3d printer files listed in the 3d parts section of this Github or listed in the BOM above. 

### Arduboy Pro Rumble
- You can either contact me for a pcb and I can order some more, you can make your own using the schematics from the giuthub, or you can breadboard this out. Up to you. 

### Front side PCB
1. Solder the Male header pins into the middle of the PCB so that it's like a backpack for the Leonardo. The Male pins on the PCB face **DOWN** towards the Leonardo female pins. 
![backpack](/images/Assembly/fem1.jpg)

2. Solder in your two resistors top right, and the 7x tactile buttons onto the top of the board. 
3. Solder in your Screen. All the pins should line up on the left hand side. If you're breadboarding this, refer to the schematics for how to hook up the display.
  -  The only items facing the front of the PCB are the buttons and those two resistors. And the Screen

### Back Side PCB

1. Install female header pins where the broken out ICSP header is. 
2. Directly beneath the female header pins, install the third resistor. 
3. Solder in the transistor with the flat part facing up, curved part towards the bottom. 
4. Solder in the diode with the white stripe facing the way it is on the board. Once again refer to the schematic for help, or the pictures on the pcb. 
5. Install the capacitor with negative stripe facing the right. 

![rumble](/images/Assembly/vibmotor.jpg)


- I would install the Speaker, vibraating motor, and RGBLED on the back of the PCB. 

6. The vibrating motor goes on the two holes to the right of the capacitor circuit. Install the vibrating motor with ground wire on the left. (If PCB back is facing you.)

7. The speaker is labeled for the front, but I find it works better on the bottom of the board. the speaker wire holes are directly left of the diode.(If PCB back is facing you.) Solder in the piezo speaker with the positive wire on the left.

8. The serial cable wires are also labeled for the top, but I like them better on the bottom. You should be able to see the traces on the PCB. If the back of the OCB is facing you RX is the left hole of the gold pads. TX is the right. (the front of the board has them labeled as JP1.)

9. You're also going to need to tack a ground wire onto one of the nubs of a ground wire, as you need this for serial and I forgot. 
- This illustrates the ground wire, but the other wires are on top, which I mentioned not to do. 

![Ground](/images/Assembly/groundwire.jpg)

##
## At this point you should be able to backpack the PCB onto the Leonardo
##
### Now we need to make the booster cables so we can power up the arduino.
  - You should probably hook everything up to your data cable at this point and run the included "Rumble Demo" to make sure everything's working right. We're about to cut up that data cable so, test it now, anyway. 
  -
  
 ## Powerboost and Booster Cables
 
 1. Follow the directions from Adafruit to hook up a switch to your Powerboost. You're going to want to mount the switch with wires instead of directly to the board so we cna remote mount it. 
  - https://learn.adafruit.com/adafruit-powerboost-500-plus-charger/on-slash-off-switch
  
  
  - ![onOff](/images/Assembly/onOff.jpg)

### You may as well wire up both powerboosts, and make two boost cables. We need the boost cables to be able to pass data through . 

2. https://learn.adafruit.com/booster-cable

## It's Time To
## Shove thaat thang in the case.
### Let me just preface this with I didn't know the powerboost would take up so much room. They look so small. 
### And I'm new to Fusion360. 
#### Sowwy. 
#### Do your best to put everything in the case and rout the USB out the top holes, and the Serial cable out the bottom. It's pretty self explanatory so here are some pictures of how I did it. Feel free to design your own case at this point. 

#### Glue down the Piezo and the vibrating motor to the back inside of the, where the empty resources are. You probably want to add a few dabs of glue to the front part of the case to keep your d pad in place, too. 

![inthere](/images/Assembly/inthere.jpg)

![inthere](/images/Assembly/CaseTop.jpg)

![inthere](/images/Assembly/casebottom.jpg)


## Should look like this 
![done](/images/prorumble.JPG)



## Ardumiibo Scanner Assembly

1. On the **PN532 NFC RFID module** Solder on the 4 90 degree pins that came with your module so that they are sticking out the side that reads "TXD RXD"
2. Carefully switch the module to IIC/ I2c mode by flipping the jumper. 
  - More info can be found here: https://www.electroschematics.com/nfc-rfid-module-pn532/
  - And here: http://wiki.sunfounder.cc/index.php?title=PN532_NFC_RFID_Module
3. The Arduino Pro Micro will sit in the bottom of the Scanner case, along with the Powerboost hooked up to it's booster cable
 - https://learn.adafruit.com/booster-cable
4. The middle bdoy is where the PN532 will sit, and you will pass wires through the holes to the bottom of the case.  (If you've printed the case this will be very evident.)
5. The top faceplate is in 3 parts, and the NEOPIXEL ring is glued into the back of the light diffuser ring part. 
6. Run the wires from the top section of the box where the LEDs are, THrough the body, and into the base so you can solder them into the Pro Micro as follows. 


Pro Micro | Module
------------ | -------------
VCC | VCC PN532
VCC | 5v LED Ring 
GND | GND PN532
GND | GND LED Ring
Pin 2 | PN532/ SDA
PIN 3 | PN532/ SCL
PIN 4 | LED Ring Data In


![RFIDclose](/images/Assembly/Scanner/rfidcloseup.jpg)

![ScanTop](/images/Assembly/Scanner/scannertop.jpg)

### Unfortunately I can't show you the wires in the pro micro because fitting everything in the box is a hard task. Once it's in there, it's in. 
 - Use plenty of hot glue for attaching and wire stress relief. 



## Software

- I use the Arduino IDE so I can't speak to the Arduboy game loaders. 
- Use Mr Blinky's homemade Package for running the 1309. Select Homemade Arduboy, Leonardo, and SSD1309. Standard Arduino Core.
  - https://github.com/MrBlinky/Arduboy-homemade-package
  - Blinky's software worked for me out of the box, but I remember way back having to change some addresses or running the patcher for uploading games. You can find out all about that on the Arduboy forums and in Mr. Blinky's docs. 

- Install the PN532 Arduino Library
  - https://github.com/Seeed-Studio/PN532/tree/arduino/PN532

- Install the Adafruit Neopixel Library 
  - https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation

### Load your scanner Pro Micro up with the NFC Reader 

- (https://github.com/wimberlyw/ardumiibo/tree/main/Scanner%20Programs)
    -  This is basically boilperplate from the PN532 libraries, and the Adafruit Neopixel library.

### Load your Arduboy Pro Rumble up with the example ScanDemo

-https://github.com/wimberlyw/ardumiibo/tree/main/Examples
 
 ### Check out the video tutorial on how to make an Ardumiibo. 
 
 - https://youtu.be/rNLjulla09I
  - Use the word "keys" for the key example
  - Use "pots" for the potion example. 
  - Try Everything out!
 
 ## Try the "Turbo Waddle" Demo!
 
 - https://youtu.be/9yPsy_AzS58
 - https://github.com/wimberlyw/ardumiibo/tree/main/Game/TurboWaddle

## Make your own game with Rumble!

- Rumble just uses the Tone library BeepPin2. 
- Essentially The scanner is just passign a string over serial. 
  -  Read the examples!


```BeepPin2 rumble; // Rumble motor runs on Speaker Pin 2

void setup() 
{rumble.begin();//Set up Rumble Motor}
  
	 if (arduboy.justPressed(B_BUTTON)) {

	rumble.tone(beep.freq(523.251), 5); /beep.freq(523.251) is used to convert 523.251Hz to the required count
	} 
```
 
## Make your own game with Ardumiibo Support!
1. Turn on :
  - ` power_usart1_enable(); // Arduboy turns off serial power, so we need that to connect to the RFID reader`
  -  `Serial1.begin(115200);// Begin communication with the Serial port/ Reader over Serial 1"` 

 2. Set up a dummy string to save the message we receive from Serial. 
`String Message;//Storing messages from the scanner as a string here. `

3. If the Serial is receiving a message, check to see if it's ours.
- If it is, do something. 

**THIS LINE MAKES SERIAL NOT LOCK UP EVERYTHING BY SCANNING ALL THE TIME, BUT ONLY WHEN DATA COMES
You could do a "Blocking" version if you wanted the user to be stuck somewhere until they scan something.  Just don't include serial available.**

`if(Serial1.available()){  
   Message = Serial1.readStringUntil('\r');     //Store incoming data `
   

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
           


### **That's really all you need to set up your game to read from the scanner!**


