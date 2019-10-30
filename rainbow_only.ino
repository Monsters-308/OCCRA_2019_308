/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
 * 
 * 


 The intention of the application is to control NeoPixels based on 
 Serial communications from a Vex Cortex controller UART1
 The Vex Cortex must be setup with UART1 set to 9600 baud
 the Vex Cortex wiring UART1 Tx must be wired to the Arduino Uno Pin 3(RX)
 The Vex Cortex wiring UART1 Rx must be wired to the Arduino Uno Pin 2(TX)

 The NeoPixel Library must have the control pin on pin 
*/

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      93


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


SoftwareSerial mySerial(2, 3); // RX, TX pins on the Arduion Uno 

//void setRed(void);
//void setGreen(void);
//void defaultLeds(void);
//void clearLeds(void);
void rainbow(int wait);

int ledState = 0;
//bool initState = false;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600); // local port for debugging
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600); // what is the baud rate of the second device
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  ledState = 0;
}


void loop() // run over and over
{
  rainbow(100);
  /*int readState = 0;

  if(initState == false){
    defaultLeds();
    initState = true;
  }
  
  if (mySerial.available()){
    readState = mySerial.read();    
    
    if(ledState != readState){ // this means a state change
      // we must have a new change to the led's

      switch(readState){
        case 0: // this would be the initilization state
          defaultLeds();
          break;

        case 1: // this would be normal coms with gripper open
          setRed();
          break;

        case 2: // this would be normal communication with gripper closed
          setGreen();
          break;

        default: // default state incase of any error
          defaultLeds();
          break;
      }

      ledState = readState;
          // when done set the letState to the new readState
    }
  } 
}


// set the pixels to red
void setRed(){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(150,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.


  }
}

// set the pixels to green
void setGreen(){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.


  }
}

void clearLeds(){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

*/
  
}
// set a default loop for the pixels
void defaultLeds(){
  rainbow(100);
}

void rainbow(int wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
