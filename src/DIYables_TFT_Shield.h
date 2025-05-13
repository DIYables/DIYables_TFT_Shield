#ifndef DIYables_TFT_Shield_H
#define DIYables_TFT_Shield_H

#include <Arduino.h>
#include <Adafruit_GFX.h>

// Data pins mapping
#define D0_PIN 8
#define D1_PIN 9
#define D2_PIN 2
#define D3_PIN 3
#define D4_PIN 4
#define D5_PIN 5
#define D6_PIN 6
#define D7_PIN 7

// Control pins
#define API_PIN_RD   A0
#define API_PIN_WR   A1
#define API_PIN_CD   A2
#define API_PIN_CS   A3
#define API_PIN_RESET  A4

class DIYables_TFT_ILI9486_Shield : public Adafruit_GFX {
public:
  DIYables_TFT_ILI9486_Shield();
  void begin();
  void fillScreen(uint16_t color) override;
  void setRotation(uint8_t r) override;
  void invertDisplay(bool i) override;

  /**
   * Convert 8-bit R,G,B to 16-bit 565 color format.
   */
  static uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  }

  void drawPixel(int16_t x, int16_t y, uint16_t color) override;

private:
  inline void reset();
  inline void writeCommand(uint8_t cmd);
  inline void writeData(uint8_t data);
  inline void write8(uint8_t val);
  inline void pulseWR();
  inline void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  void setWriteDir();
  void writeData16(uint16_t data, uint32_t count);
};

#endif // DIYables_TFT_Shield_H