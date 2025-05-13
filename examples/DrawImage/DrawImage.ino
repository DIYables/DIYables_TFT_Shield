/*
   Created by DIYables

   This example code is in the public domain

   Product page:
   - https://diyables.io/products/3.5-inch-color-tft-lcd-display-screen-module-320x480-non-touch-for-arduino-uno-and-mega-ili9486-8-bit-parallel-interface
   - https://www.amazon.com/dp/B0DLMV7NTK
*/

#include <DIYables_TFT_Shield.h>
#include "bitmap.h"

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GREY 0x8410
#define ORANGE 0xE880

DIYables_TFT_ILI9486_Shield TFT_display;

int img_width = 120;
int img_height = 53;

uint16_t SCREEN_WIDTH;
uint16_t SCREEN_HEIGHT;

void setup() {
  Serial.begin(9600);

  Serial.println(F("Arduino TFT LCD Display"));

  TFT_display.begin();

  SCREEN_WIDTH = TFT_display.width();
  SCREEN_HEIGHT = TFT_display.height();

  int x = (SCREEN_WIDTH - img_width) / 2;
  int y = (SCREEN_HEIGHT - img_height) / 2;

  TFT_display.fillScreen(WHITE);
  TFT_display.drawRGBBitmap(x, y, myBitmap, img_width, img_height);
}

void loop(void) {
  delay(2000);
  TFT_display.invertDisplay(true);
  
  delay(2000);
  TFT_display.invertDisplay(false);
}
