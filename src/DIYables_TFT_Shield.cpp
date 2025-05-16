#include <DIYables_TFT_Shield.h>

DIYables_TFT_ILI9486_Shield::DIYables_TFT_ILI9486_Shield()
  : Adafruit_GFX(320, 480) {}

void DIYables_TFT_ILI9486_Shield::begin() {
  SET_DATA_DIR_OUT();
  SET_CONTROL_DIR_OUT();

  #ifndef ARDUINO_API_USED
  PIN_HIGH(RD_PORT, RD_PIN);
  #else
  PIN_HIGH(API_PIN_RD);
  #endif
  
  
  #ifndef ARDUINO_API_USED
  PIN_LOW(CS_PORT, CS_PIN);
  #else
  PIN_LOW(API_PIN_CS);
  #endif

  reset();

  writeCommand(0x11); // Sleep out
  delay(120);
  writeCommand(0xD0); // Power Setting
  writeData(0x07);
  writeData(0x42);
  writeData(0x18);
  writeCommand(0xD1); // VCOM Control
  writeData(0x00);
  writeData(0x07);
  writeData(0x10);
  writeCommand(0x36); // Memory Access Control
  writeData(0x48);    // MX, BGR
  writeCommand(0x3A); // Interface Pixel Format
  writeData(0x55);    // 16-bit/pixel
  writeCommand(0xC5); // Frame Rate Control
  writeData(0x10);
  writeCommand(0xC8); // Gamma Adjustment
  writeData(0x00); writeData(0x32); writeData(0x36);
  writeData(0x45); writeData(0x06); writeData(0x16);
  writeData(0x37); writeData(0x75); writeData(0x77);
  writeData(0x54); writeData(0x0C); writeData(0x00);
  writeCommand(0x13); // Normal Display Mode
  writeCommand(0x29); // Display ON
  delay(50);
}

void DIYables_TFT_ILI9486_Shield::fillScreen(uint16_t color) {
  setAddrWindow(0, 0, width() - 1, height() - 1);
  writeData16(color, (uint32_t)width() * height());
}

inline void DIYables_TFT_ILI9486_Shield::reset() {
  #ifndef ARDUINO_API_USED
  PIN_LOW(RESET_PORT, RESET_PIN);
  #else
  PIN_LOW(API_PIN_RESET);
  #endif

  delay(20);
  #ifndef ARDUINO_API_USED
  PIN_HIGH(RESET_PORT, RESET_PIN);
  #else
  PIN_HIGH(API_PIN_RESET);
  #endif
  
  delay(120);
}

void DIYables_TFT_ILI9486_Shield::setWriteDir() {
  SET_DATA_DIR_OUT();
}

inline void DIYables_TFT_ILI9486_Shield::write8(uint8_t val) {
  WRITE_8(val);
  #ifndef ARDUINO_API_USED
  PIN_LOW(WR_PORT, WR_PIN);
  asm volatile("nop");
  #else
  PIN_LOW(API_PIN_WR);
  #endif

  #ifndef ARDUINO_API_USED
  PIN_HIGH(WR_PORT, WR_PIN);
  #else
  PIN_HIGH(API_PIN_WR);
  #endif
}

inline void DIYables_TFT_ILI9486_Shield::pulseWR() {
  #ifndef ARDUINO_API_USED
  PIN_LOW(WR_PORT, WR_PIN);
  asm volatile("nop");
  #else
  PIN_LOW(API_PIN_WR);
  __asm__ volatile ("nop");
  #endif
  
  #ifndef ARDUINO_API_USED
  PIN_HIGH(WR_PORT, WR_PIN);
  #else
  PIN_HIGH(API_PIN_WR);
  #endif
  
}

inline void DIYables_TFT_ILI9486_Shield::writeCommand(uint8_t cmd) {
  #ifndef ARDUINO_API_USED
  PIN_LOW(CD_PORT, CD_PIN);
  #else
  PIN_LOW(API_PIN_CD);
  #endif
  write8(cmd);
}

inline void DIYables_TFT_ILI9486_Shield::writeData(uint8_t data) {
  #ifndef ARDUINO_API_USED
  PIN_HIGH(CD_PORT, CD_PIN);
  #else
  PIN_HIGH(API_PIN_CD);
  #endif
  write8(data);
}

void DIYables_TFT_ILI9486_Shield::writeData16(uint16_t data, uint32_t count) {
  uint8_t hi = data >> 8;
  uint8_t lo = data & 0xFF;
  
  #ifndef ARDUINO_API_USED
  PIN_HIGH(CD_PORT, CD_PIN);
  #else
  PIN_HIGH(API_PIN_CD);
  #endif

  while (count >= 8) {
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    write8(hi); pulseWR(); write8(lo); pulseWR();
    count -= 8;
  }
  while (count--) {
    write8(hi); pulseWR();
    write8(lo); pulseWR();
  }
}

inline void DIYables_TFT_ILI9486_Shield::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  writeCommand(0x2A);
  writeData(x0 >> 8); writeData(x0 & 0xFF);
  writeData(x1 >> 8); writeData(x1 & 0xFF);

  writeCommand(0x2B);
  writeData(y0 >> 8); writeData(y0 & 0xFF);
  writeData(y1 >> 8); writeData(y1 & 0xFF);

  writeCommand(0x2C);
}

void DIYables_TFT_ILI9486_Shield::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
  setAddrWindow(x, y, x, y);
  writeData(color >> 8);
  writeData(color & 0xFF);
}

void DIYables_TFT_ILI9486_Shield::setRotation(uint8_t r) {
  Adafruit_GFX::setRotation(r);
  writeCommand(0x36);
  writeData(r == 0 ? 0x48 :
            r == 1 ? 0x28 :
            r == 2 ? 0x88 :
                     0xE8);
}

void DIYables_TFT_ILI9486_Shield::invertDisplay(bool i) {
  writeCommand(i ? 0x21 : 0x20);
}