/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
// Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Thermocouple
#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16

// Thermocouple
#define MAXDO   3
#define MAXCS   4
#define MAXCLK  5

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);


static unsigned char PROGMEM const logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // draw a single pixel
  //display.drawPixel(10, 10, WHITE);
  //display.display();
  //delay(2000);
  //display.clearDisplay();

  display.clearDisplay();

  pinMode(13, OUTPUT);
}


void loop() {
  int sensorValue = analogRead(A2); // Max value around 1000
  float maxValue = 1000.0;
  int baseTemperatureRange = -15;
  int range = 50;
  float unit = range/maxValue;
  float threshold = baseTemperatureRange + unit*sensorValue;
  
  double c = thermocouple.readCelsius();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.println("");
  display.print("Temp:");
  display.println(c);
  display.print("Thres:");
  display.println(threshold);
  display.display();

  if (c > threshold) {
  digitalWrite(13, HIGH);
}  else {
  digitalWrite(13, LOW);
  }
  delay(500);
  display.clearDisplay();
}
