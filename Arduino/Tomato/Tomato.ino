#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "plant.h"

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IO
#define PIN_D_LIGHT 2
#define PIN_D_MOTOR 3
#define PIN_D_HEATER 4
#define PIN_D_FAN 5

#define PIN_A_BUTTONS A0


// Prototypes
void init(void);
void IOinit(void);
void OLEDinit(void);


void setup() {
  init();
}


void loop() {
  // put your main code here, to run repeatedly:

}

void init(void){
  IOinit();
  OLEDinit();
}

void IOinit(void){
  pinMode(PIN_D_LIGHT, OUTPUT);
  pinMode(PIN_D_MOTOR, OUTPUT);
  pinMode(PIN_D_HEATER, OUTPUT);
  pinMode(PIN_D_FAN, OUTPUT);
}

void OLEDinit(void){
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    
  }
}
