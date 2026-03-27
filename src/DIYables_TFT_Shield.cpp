#include <DIYables_TFT_Shield.h>

DIYables_TFT_ILI9486_Shield::DIYables_TFT_ILI9486_Shield()
  : Adafruit_GFX(320, 480) {
  _d[0] = D0_PIN; _d[1] = D1_PIN; _d[2] = D2_PIN; _d[3] = D3_PIN;
  _d[4] = D4_PIN; _d[5] = D5_PIN; _d[6] = D6_PIN; _d[7] = D7_PIN;
  _rd = API_PIN_RD; _wr = API_PIN_WR; _cd = API_PIN_CD;
  _cs = API_PIN_CS; _rst = API_PIN_RESET;
  _useAPI = false;
}

DIYables_TFT_ILI9486_Shield::DIYables_TFT_ILI9486_Shield(
  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
  uint8_t rd, uint8_t wr, uint8_t cd, uint8_t cs, uint8_t rst)
  : Adafruit_GFX(320, 480) {
  _d[0] = d0; _d[1] = d1; _d[2] = d2; _d[3] = d3;
  _d[4] = d4; _d[5] = d5; _d[6] = d6; _d[7] = d7;
  _rd = rd; _wr = wr; _cd = cd; _cs = cs; _rst = rst;
  _useAPI = true;
}

inline void DIYables_TFT_ILI9486_Shield::writeBus(uint8_t val) {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    WRITE_8(val);
  } else
  #endif
  {
    digitalWrite(_d[0], (val >> 0) & 0x01);
    digitalWrite(_d[1], (val >> 1) & 0x01);
    digitalWrite(_d[2], (val >> 2) & 0x01);
    digitalWrite(_d[3], (val >> 3) & 0x01);
    digitalWrite(_d[4], (val >> 4) & 0x01);
    digitalWrite(_d[5], (val >> 5) & 0x01);
    digitalWrite(_d[6], (val >> 6) & 0x01);
    digitalWrite(_d[7], (val >> 7) & 0x01);
  }
}

void DIYables_TFT_ILI9486_Shield::begin() {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    SET_DATA_DIR_OUT();
    SET_CONTROL_DIR_OUT();
  } else
  #endif
  {
    for (uint8_t i = 0; i < 8; i++) { pinMode(_d[i], OUTPUT); }
    pinMode(_rd, OUTPUT);
    pinMode(_wr, OUTPUT);
    pinMode(_cd, OUTPUT);
    pinMode(_cs, OUTPUT);
    pinMode(_rst, OUTPUT);
  }

  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(RD_PORT, RD_PIN);
  } else
  #endif
  {
    digitalWrite(_rd, HIGH);
  }
  
  
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_LOW(CS_PORT, CS_PIN);
  } else
  #endif
  {
    digitalWrite(_cs, LOW);
  }

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
  if (!_useAPI) {
    PIN_LOW(RESET_PORT, RESET_PIN);
  } else
  #endif
  {
    digitalWrite(_rst, LOW);
  }

  delay(20);
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(RESET_PORT, RESET_PIN);
  } else
  #endif
  {
    digitalWrite(_rst, HIGH);
  }
  
  delay(120);
}

void DIYables_TFT_ILI9486_Shield::setWriteDir() {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    SET_DATA_DIR_OUT();
  } else
  #endif
  {
    for (uint8_t i = 0; i < 8; i++) { pinMode(_d[i], OUTPUT); }
  }
}

inline void DIYables_TFT_ILI9486_Shield::write8(uint8_t val) {
  writeBus(val);
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_LOW(WR_PORT, WR_PIN);
    asm volatile("nop");
  } else
  #endif
  {
    digitalWrite(_wr, LOW);
  }

  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(WR_PORT, WR_PIN);
  } else
  #endif
  {
    digitalWrite(_wr, HIGH);
  }
}

inline void DIYables_TFT_ILI9486_Shield::pulseWR() {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_LOW(WR_PORT, WR_PIN);
    asm volatile("nop");
  } else
  #endif
  {
    digitalWrite(_wr, LOW);
    __asm__ volatile ("nop");
  }
  
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(WR_PORT, WR_PIN);
  } else
  #endif
  {
    digitalWrite(_wr, HIGH);
  }
  
}

inline void DIYables_TFT_ILI9486_Shield::writeCommand(uint8_t cmd) {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_LOW(CD_PORT, CD_PIN);
  } else
  #endif
  {
    digitalWrite(_cd, LOW);
  }
  write8(cmd);
}

inline void DIYables_TFT_ILI9486_Shield::writeData(uint8_t data) {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(CD_PORT, CD_PIN);
  } else
  #endif
  {
    digitalWrite(_cd, HIGH);
  }
  write8(data);
}

void DIYables_TFT_ILI9486_Shield::writeData16(uint16_t data, uint32_t count) {
  uint8_t hi = data >> 8;
  uint8_t lo = data & 0xFF;

  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(CD_PORT, CD_PIN);
    if (hi == lo) {
      WRITE_8(hi);
      while (count >= 8) {
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        count -= 8;
      }
      while (count--) {
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
      }
    } else {
      while (count >= 8) {
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        count -= 8;
      }
      while (count--) {
        WRITE_8(hi); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(lo); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
      }
    }
    return;
  }
  #endif

  // API path
  digitalWrite(_cd, HIGH);
  if (hi == lo) {
    writeBus(hi);
    while (count >= 8) {
      pulseWR(); pulseWR(); pulseWR(); pulseWR();
      pulseWR(); pulseWR(); pulseWR(); pulseWR();
      pulseWR(); pulseWR(); pulseWR(); pulseWR();
      pulseWR(); pulseWR(); pulseWR(); pulseWR();
      count -= 8;
    }
    while (count--) {
      pulseWR(); pulseWR();
    }
  } else {
    while (count >= 8) {
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      writeBus(hi); pulseWR(); writeBus(lo); pulseWR();
      count -= 8;
    }
    while (count--) {
      writeBus(hi); pulseWR();
      writeBus(lo); pulseWR();
    }
  }
}

void DIYables_TFT_ILI9486_Shield::setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    // Command 0x2A (Column Address Set)
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2A); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_HIGH(CD_PORT, CD_PIN);
    WRITE_8(x0 >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x0 & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x1 >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x1 & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    // Command 0x2B (Row Address Set)
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2B); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_HIGH(CD_PORT, CD_PIN);
    WRITE_8(y0 >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y0 & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y1 >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y1 & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    // Command 0x2C (Memory Write)
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2C); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    return;
  }
  #endif

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

  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    // Inline setAddrWindow
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2A); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_HIGH(CD_PORT, CD_PIN);
    WRITE_8(x >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(x & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2B); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_HIGH(CD_PORT, CD_PIN);
    WRITE_8(y >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(y & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    PIN_LOW(CD_PORT, CD_PIN);
    WRITE_8(0x2C); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    // Write pixel color
    PIN_HIGH(CD_PORT, CD_PIN);
    WRITE_8(color >> 8);   PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    WRITE_8(color & 0xFF); PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    return;
  }
  #endif

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

void DIYables_TFT_ILI9486_Shield::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if (x >= width() || y >= height() || w <= 0 || h <= 0) return;
  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }
  if ((x + w) > width())  w = width()  - x;
  if ((y + h) > height()) h = height() - y;

  setAddrWindow(x, y, x + w - 1, y + h - 1);
  writeData16(color, (uint32_t)w * h);
}

void DIYables_TFT_ILI9486_Shield::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  fillRect(x, y, w, 1, color);
}

void DIYables_TFT_ILI9486_Shield::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  fillRect(x, y, 1, h, color);
}

void DIYables_TFT_ILI9486_Shield::pushColors(uint16_t *data, uint32_t len) {
  #ifndef ARDUINO_API_USED
  if (!_useAPI) {
    PIN_HIGH(CD_PORT, CD_PIN);
    while (len--) {
      uint16_t color = *data++;
      WRITE_8(color >> 8);
      PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
      WRITE_8(color & 0xFF);
      PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
    }
    return;
  }
  #endif

  digitalWrite(_cd, HIGH);
  while (len--) {
    uint16_t color = *data++;
    writeBus(color >> 8); pulseWR();
    writeBus(color & 0xFF); pulseWR();
  }
}

void DIYables_TFT_ILI9486_Shield::drawRGBBitmap(int16_t x, int16_t y,
  const uint16_t bitmap[], int16_t w, int16_t h) {
  if (x >= width() || y >= height() || (x + w) <= 0 || (y + h) <= 0) return;

  if (x >= 0 && y >= 0 && (x + w) <= width() && (y + h) <= height()) {
    setAddrWindow(x, y, x + w - 1, y + h - 1);

    uint32_t count = (uint32_t)w * h;

    #ifndef ARDUINO_API_USED
    if (!_useAPI) {
      PIN_HIGH(CD_PORT, CD_PIN);
      for (uint32_t i = 0; i < count; i++) {
        uint16_t color = pgm_read_word(&bitmap[i]);
        WRITE_8(color >> 8);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
        WRITE_8(color & 0xFF);
        PIN_LOW(WR_PORT, WR_PIN); asm volatile("nop"); PIN_HIGH(WR_PORT, WR_PIN);
      }
    } else
    #endif
    {
      digitalWrite(_cd, HIGH);
      for (uint32_t i = 0; i < count; i++) {
        uint16_t color = pgm_read_word(&bitmap[i]);
        writeBus(color >> 8); pulseWR();
        writeBus(color & 0xFF); pulseWR();
      }
    }
  } else {
    for (int16_t j = 0; j < h; j++) {
      for (int16_t i = 0; i < w; i++) {
        int16_t px = x + i, py = y + j;
        if (px >= 0 && px < width() && py >= 0 && py < height()) {
          drawPixel(px, py, pgm_read_word(&bitmap[j * w + i]));
        }
      }
    }
  }
}

void DIYables_TFT_ILI9486_Shield::drawRGBBitmap(int16_t x, int16_t y,
  uint16_t *bitmap, int16_t w, int16_t h) {
  if (x >= width() || y >= height() || (x + w) <= 0 || (y + h) <= 0) return;

  if (x >= 0 && y >= 0 && (x + w) <= width() && (y + h) <= height()) {
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    pushColors(bitmap, (uint32_t)w * h);
  } else {
    for (int16_t j = 0; j < h; j++) {
      for (int16_t i = 0; i < w; i++) {
        int16_t px = x + i, py = y + j;
        if (px >= 0 && px < width() && py >= 0 && py < height()) {
          drawPixel(px, py, bitmap[j * w + i]);
        }
      }
    }
  }
}