/*
   Created by DIYables

   This example code is in the public domain

   Product page:
   - https://diyables.io/products/3.5-inch-color-tft-lcd-display-screen-module-320x480-non-touch-for-arduino-uno-and-mega-ili9486-8-bit-parallel-interface
   - https://www.amazon.com/dp/B0DLMV7NTK
*/

#include <DIYables_TFT_Shield.h>

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
#define PINK 0xF81F
#define LIME 0x07FF
#define VIOLET 0x915C
#define GOLD 0xFEA0
#define TURQUOISE 0x471A

DIYables_TFT_ILI9486_Shield TFT_display;

// Helper to draw a filled diamond
void fillDiamond(int cx, int cy, int h, int v, uint16_t color) {
  int x0 = cx, y0 = cy - v;
  int x1 = cx + h, y1 = cy;
  int x2 = cx, y2 = cy + v;
  int x3 = cx - h, y3 = cy;
  TFT_display.fillTriangle(x0, y0, x1, y1, x2, y2, color);
  TFT_display.fillTriangle(x0, y0, x2, y2, x3, y3, color);
}

void setup() {
  TFT_display.begin();
  TFT_display.setRotation(1);  // Landscape: 480x320
}

void loop() {
  TFT_display.fillScreen(BLACK);

  // Outlined circle (top left)
  TFT_display.drawCircle(70, 60, 40, RED);

  // Filled circle (top center)
  TFT_display.fillCircle(180, 60, 40, RED);

  // Outlined triangle (top right)
  TFT_display.drawTriangle(260, 30, 340, 30, 300, 100, BLUE);

  // Filled triangle (top far right)
  TFT_display.fillTriangle(370, 30, 450, 30, 410, 100, LIME);

  // Outlined rectangle (middle left)
  TFT_display.drawRect(30, 130, 80, 50, ORANGE);

  // Filled rectangle (middle center)
  TFT_display.fillRect(140, 130, 80, 50, TURQUOISE);

  // Outlined round rectangle (middle right)
  TFT_display.drawRoundRect(260, 130, 80, 50, 15, VIOLET);

  // Filled round rectangle (middle far right)
  TFT_display.fillRoundRect(370, 130, 80, 50, 15, PINK);

  // Outlined diamond shape (bottom left)
  int cx1 = 120, cy1 = 250, h1 = 40, v1 = 50;
  TFT_display.drawLine(cx1, cy1 - v1, cx1 + h1, cy1, GREEN);
  TFT_display.drawLine(cx1 + h1, cy1, cx1, cy1 + v1, GREEN);
  TFT_display.drawLine(cx1, cy1 + v1, cx1 - h1, cy1, GREEN);
  TFT_display.drawLine(cx1 - h1, cy1, cx1, cy1 - v1, GREEN);

  // Filled diamond shape (bottom right)
  int cx2 = 355, cy2 = 250, h2 = 40, v2 = 50;
  fillDiamond(cx2, cy2, h2, v2, BLUE);

  delay(10000);
}