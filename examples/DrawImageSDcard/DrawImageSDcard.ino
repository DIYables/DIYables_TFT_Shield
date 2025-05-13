/*
   Created by DIYables

   This example code is in the public domain

   Product page:
   - https://diyables.io/products/3.5-inch-color-tft-lcd-display-screen-module-320x480-non-touch-for-arduino-uno-and-mega-ili9486-8-bit-parallel-interface
   - https://www.amazon.com/dp/B0DLMV7NTK
*/

#include <DIYables_TFT_Shield.h>
#include <SD.h>

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

#define BUFFPIXEL 20  // Buffer size remains the same

DIYables_TFT_ILI9486_Shield TFT_display;
#define SD_CS 10

File bmpFile;
uint16_t SCREEN_WIDTH;
uint16_t SCREEN_HEIGHT;

void setup() {
  Serial.begin(9600);
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized successfully.");

  Serial.println(F("Arduino TFT LCD Display"));

  TFT_display.begin();

  // Set the rotation (0 to 3)
  TFT_display.setRotation(1);  // Rotate screen 90 degrees

  // After rotation, update screen dimensions
  SCREEN_WIDTH = TFT_display.width();
  SCREEN_HEIGHT = TFT_display.height();

  TFT_display.fillScreen(WHITE);

  // Get image dimensions
  uint32_t imgWidth, imgHeight;
  if (getBMPDimensions("diyables.bmp", imgWidth, imgHeight)) {
    Serial.print("BMP Image Width: ");
    Serial.println(imgWidth);
    Serial.print("BMP Image Height: ");
    Serial.println(imgHeight);
  } else {
    Serial.println("Failed to get BMP dimensions");
  }

  // Optionally, center the image based on its dimensions
  int x = (SCREEN_WIDTH - imgWidth) / 2;
  int y = (SCREEN_HEIGHT - imgHeight) / 2;

  drawBMP("diyables.bmp", x, y);  // Draw image at calculated position
}

void loop(void) {
}

// Helper functions to read BMP file header
uint16_t read16(File &f) {
  uint16_t result;
  result = f.read();
  result |= (f.read() << 8);
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  result = f.read();
  result |= ((uint32_t)f.read() << 8);
  result |= ((uint32_t)f.read() << 16);
  result |= ((uint32_t)f.read() << 24);
  return result;
}

// Function to read a signed 32-bit integer
int32_t readS32(File &f) {
  int32_t result;
  result = f.read();
  result |= ((uint32_t)f.read() << 8);
  result |= ((uint32_t)f.read() << 16);
  result |= ((uint32_t)f.read() << 24);
  return result;
}

// Function to draw BMP from SD card
void drawBMP(const char *filename, int x, int y) {
  bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.println("File not found");
    return;
  }

  if (read16(bmpFile) != 0x4D42) {  // Check BMP signature
    Serial.println("Not a BMP file");
    bmpFile.close();
    return;
  }

  // Skip unnecessary BMP header details
  Serial.println("BMP signature OK");

  uint32_t fileSize = read32(bmpFile);
  Serial.print("File Size: ");
  Serial.println(fileSize);

  read32(bmpFile);                         // Reserved bytes (skip)
  uint32_t imageOffset = read32(bmpFile);  // Start of image data
  Serial.print("Image Data Offset: ");
  Serial.println(imageOffset);

  uint32_t dibHeaderSize = read32(bmpFile);  // DIB header size
  Serial.print("DIB Header Size: ");
  Serial.println(dibHeaderSize);

  // Now read the width and height of the image
  uint32_t bmpWidth = read32(bmpFile);
  int32_t bmpHeight = readS32(bmpFile);  // Read as signed 32-bit integer
  Serial.print("Image Width: ");
  Serial.println(bmpWidth);
  Serial.print("Image Height: ");
  Serial.println(bmpHeight);

  bool topDown = false;  // Flag to check if the image is top-down
  if (bmpHeight < 0) {
    bmpHeight = -bmpHeight;  // Make height positive for processing
    topDown = true;          // Mark the BMP as top-down
  }

  if (read16(bmpFile) != 1) {  // Planes must be 1
    Serial.println("Invalid BMP file");
    bmpFile.close();
    return;
  }

  uint16_t depth = read16(bmpFile);  // Color depth
  Serial.print("Bit Depth: ");
  Serial.println(depth);

  if (depth != 24) {  // Only 24-bit BMP supported
    Serial.println("Only 24-bit BMP is supported");
    bmpFile.close();
    return;
  }

  if (read32(bmpFile) != 0) {  // No compression
    Serial.println("Unsupported BMP compression");
    bmpFile.close();
    return;
  }

  // Move to the start of the image data
  bmpFile.seek(imageOffset);

  uint8_t sdbuffer[3 * BUFFPIXEL];  // Buffer for 20 pixels (3 bytes per pixel)
  uint16_t color;
  uint32_t rowSize = (bmpWidth * 3 + 3) & ~3;  // BMP rows are padded to 4-byte boundaries

  // Adjust x and y if image is larger than screen
  if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
    Serial.println("Image position out of screen bounds");
    return;
  }

  uint32_t maxRow = min(bmpHeight, SCREEN_HEIGHT - y);
  uint32_t maxCol = min(bmpWidth, SCREEN_WIDTH - x);

  // Draw the image
  for (uint32_t row = 0; row < maxRow; row++) {
    int32_t rowPos = topDown ? row : bmpHeight - 1 - row;  // Adjust for top-down BMPs

    uint32_t filePosition = imageOffset + rowPos * rowSize;
    bmpFile.seek(filePosition);  // Move to the correct row

    for (uint32_t col = 0; col < maxCol; col += BUFFPIXEL) {
      uint32_t pixelsToRead = min(BUFFPIXEL, maxCol - col);  // Avoid reading beyond row width
      bmpFile.read(sdbuffer, 3 * pixelsToRead);              // Read multiple pixels at once

      for (uint32_t i = 0; i < pixelsToRead; i++) {
        uint8_t b = sdbuffer[i * 3];
        uint8_t g = sdbuffer[i * 3 + 1];
        uint8_t r = sdbuffer[i * 3 + 2];
        color = TFT_display.color565(r, g, b);

        // Draw pixel on screen if within bounds
        if ((x + col + i) < SCREEN_WIDTH && (y + row) < SCREEN_HEIGHT) {
          TFT_display.drawPixel(x + col + i, y + row, color);
        }
      }
    }
  }

  bmpFile.close();  // Close file when done
  Serial.println("Finished drawing BMP");
}

// Function to get BMP image dimensions
bool getBMPDimensions(const char *filename, uint32_t &width, uint32_t &height) {
  File bmpFile = SD.open(filename);
  if (!bmpFile) {
    Serial.println("File not found");
    return false;
  }

  if (read16(bmpFile) != 0x4D42) {  // Check BMP signature
    Serial.println("Not a BMP file");
    bmpFile.close();
    return false;
  }

  read32(bmpFile);  // Skip file size
  read32(bmpFile);  // Skip reserved bytes
  uint32_t imageOffset = read32(bmpFile);  // Start of image data

  uint32_t dibHeaderSize = read32(bmpFile);  // DIB header size

  // Read the width and height of the image
  width = read32(bmpFile);
  int32_t bmpHeight = readS32(bmpFile);  // May be negative for top-down images
  height = (bmpHeight < 0) ? -bmpHeight : bmpHeight;

  bmpFile.close();  // Close the file
  return true;      // Success
}
