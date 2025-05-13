/*
   Created by DIYables

   This example code is in the public domain

   Product page:
   - https://diyables.io/products/3.5-inch-color-tft-lcd-display-screen-module-320x480-non-touch-for-arduino-uno-and-mega-ili9486-8-bit-parallel-interface
   - https://www.amazon.com/dp/B0DLMV7NTK
*/

#include <DIYables_TFT_Shield.h>
#include <Fonts/FreeSansBold12pt7b.h>

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
  Serial.println(F("Arduino TFT LCD Display - Use external font"));

  TFT_display.begin();
  TFT_display.setFont(&FreeSansBold12pt7b);

  // Set the rotation (0 to 3)
  TFT_display.setRotation(1);  // Rotate screen 90 degrees

  // After rotation, update screen dimensions
  SCREEN_WIDTH = TFT_display.width();
  SCREEN_HEIGHT = TFT_display.height();

  TFT_display.fillScreen(WHITE);

  // Set text color and size
  TFT_display.setTextColor(MAGENTA);
  TFT_display.setTextSize(1);  // Adjust text size as needed

  // Sample temperature value
  float temperature = 23.5;
  float humidity = 78.6;

  // Display temperature with degree symbol
  TFT_display.setCursor(20, 20);    // Set cursor position (x, y)
  TFT_display.print("Temperature: ");
  TFT_display.print(temperature, 1);  // Print temperature with 1 decimal place
  TFT_display.print(char(247));
  TFT_display.println("C");

  // Display humidity
  TFT_display.setCursor(20, 60);    // Set cursor position (x, y)
  TFT_display.print("Humidity: ");
  TFT_display.print(humidity, 1);   // Print humidity with 1 decimal place
  TFT_display.print("%");
}

void loop(void) {
}
