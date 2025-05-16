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

// Board-specific macros
#if defined(__AVR_ATmega328P__)
// Uno R3 (ATmega328P)
// Data pins: 8 (PB0), 9 (PB1), 2 (PD2), 3 (PD3), 4 (PD4), 5 (PD5), 6 (PD6), 7 (PD7)
// Control pins: A0 (PC0), A1 (PC1), A2 (PC2), A3 (PC3), A4 (PC4)
#define RD_PORT PORTC
#define RD_PIN  0
#define WR_PORT PORTC
#define WR_PIN  1
#define CD_PORT PORTC
#define CD_PIN  2
#define CS_PORT PORTC
#define CS_PIN  3
#define RESET_PORT PORTC
#define RESET_PIN  4

#define BMASK 0x03 // PB0-PB1 (pins 8-9)
#define DMASK 0xFC // PD2-PD7 (pins 2-7)
#define WRITE_8(x) do { \
  PORTB = (PORTB & ~BMASK) | ((x) & BMASK); \
  PORTD = (PORTD & ~DMASK) | ((x) & DMASK); \
} while(0)
#define SET_DATA_DIR_OUT() do { DDRB |= BMASK; DDRD |= DMASK; } while(0)
#define SET_CONTROL_DIR_OUT() do { \
  DDRC |= (1 << RD_PIN) | (1 << WR_PIN) | (1 << CD_PIN) | (1 << CS_PIN) | (1 << RESET_PIN); \
} while(0)
#define PIN_LOW(p, b) (p) &= ~(1 << (b))
#define PIN_HIGH(p, b) (p) |= (1 << (b))
#define PIN_OUTPUT(p, b) *(&p - 1) |= (1 << (b))

#elif defined(__AVR_ATmega2560__)
// Mega (ATmega2560)
// Data pins: PH4, PH3, PE3, PG5, PE5, PE4, PH6, PH5
// Control pins: PF0, PF1, PF2, PF3, PF4
#define RD_PORT PORTF
#define RD_PIN  0
#define WR_PORT PORTF
#define WR_PIN  1
#define CD_PORT PORTF
#define CD_PIN  2
#define CS_PORT PORTF
#define CS_PIN  3
#define RESET_PORT PORTF
#define RESET_PIN  4

#define EMASK 0x38
#define GMASK 0x20
#define HMASK 0x78
#define WRITE_8(x) do { \
  PORTH &= ~HMASK; PORTG &= ~GMASK; PORTE &= ~EMASK; \
  PORTH |= (((x) & (3 << 0)) << 5); \
  PORTE |= (((x) & (3 << 2)) << 2); \
  PORTG |= (((x) & (1 << 4)) << 1); \
  PORTE |= (((x) & (1 << 5)) >> 2); \
  PORTH |= (((x) & (3 << 6)) >> 3); \
} while(0)
#define SET_DATA_DIR_OUT() do { DDRH |= HMASK; DDRG |= GMASK; DDRE |= EMASK; } while(0)
#define SET_CONTROL_DIR_OUT() DDRF |= 0x1F
#define PIN_LOW(p, b) (p) &= ~(1 << (b))
#define PIN_HIGH(p, b) (p) |= (1 << (b))
#define PIN_OUTPUT(p, b) *(&p - 1) |= (1 << (b))

#elif defined(__SAM3X8E__)
// Due (SAM3X8E)
// Data pins: PB25-26, PC1-6
// Control pins: PA22-25, PB14
#define WRITE_8(val) do { \
  REG_PIOB_SODR = ((val & 0x03) << 25); \
  REG_PIOB_CODR = ((~val & 0x03) << 25); \
  REG_PIOC_SODR = ((val & 0xFC) << 1); \
  REG_PIOC_CODR = ((~val & 0xFC) << 1); \
} while(0)
#define SET_WR_LOW() REG_PIOA_CODR = (1 << 23)
#define SET_WR_HIGH() REG_PIOA_SODR = (1 << 23)
#define SET_RS_LOW() REG_PIOA_CODR = (1 << 24)
#define SET_RS_HIGH() REG_PIOA_SODR = (1 << 24)
#define SET_CS_LOW() REG_PIOA_CODR = (1 << 25)
#define SET_CS_HIGH() REG_PIOA_SODR = (1 << 25)
#define SET_RD_HIGH() REG_PIOA_SODR = (1 << 22)
#define SET_RST_LOW() REG_PIOB_CODR = (1 << 14)
#define SET_RST_HIGH() REG_PIOB_SODR = (1 << 14)
#define SET_DATA_DIR_OUT() do { \
  REG_PIOB_OER = (0x03 << 25); \
  REG_PIOC_OER = (0x3F << 1); \
} while(0)
#define SET_CONTROL_DIR_OUT() do { \
  REG_PIOA_OER = (0x0F << 22); \
  REG_PIOB_OER = (1 << 14); \
} while(0)
#define PIN_LOW(p, b) *(&p) &= ~(1 << (b))
#define PIN_HIGH(p, b) *(&p) |= (1 << (b))
#define PIN_OUTPUT(p, b) *(&p + 1) |= (1 << (b))


#elif defined(ARDUINO_UNOR4_MINIMA)
// Data pins: D8 (P304, P3.4), D9 (P303, P3.3), D2 (P105, P1.5), D3 (P104, P1.4), D4 (P103, P1.3), D5 (P102, P1.2), D6 (P106, P1.6), D7 (P107, P1.7)
// Control pins: A0 (P014, P0.14), A1 (P000, P0.0), A2 (P001, P0.1), A3 (P002, P0.2), A4 (P101, P1.1)

#define RD_PORT    R_PORT0
#define RD_PIN     14 // P014 (A0)
#define WR_PORT    R_PORT0
#define WR_PIN     0  // P000 (A1)
#define CD_PORT    R_PORT0
#define CD_PIN     1  // P001 (A2)
#define CS_PORT    R_PORT0
#define CS_PIN     2  // P002 (A3)
#define RESET_PORT R_PORT1
#define RESET_PIN  1  // P101 (A4)

// Data masks for port manipulation
#define DATA_PORT3 R_PORT3 // D8, D9
#define DATA_PORT1 R_PORT1 // D2-D7
#define DATA_MASK3 0x18    // P3.3 (D9), P3.4 (D8)
#define DATA_MASK1 0xFC    // P1.2 (D5), P1.3 (D4), P1.4 (D3), P1.5 (D2), P1.6 (D6), P1.7 (D7)

// Write 8 bits to the data bus
#define WRITE_8(val) do { \
    /* D8 (bit0) -> P3.4, D9 (bit1) -> P3.3 */ \
    DATA_PORT3->PODR = (DATA_PORT3->PODR & ~DATA_MASK3) \
        | (((val & 0x01) ? 0x10 : 0) | ((val & 0x02) ? 0x08 : 0)); \
    /* D2-D7: D2 (bit2) -> P1.5, D3 (bit3) -> P1.4, D4 (bit4) -> P1.3, D5 (bit5) -> P1.2, D6 (bit6) -> P1.6, D7 (bit7) -> P1.7 */ \
    DATA_PORT1->PODR = (DATA_PORT1->PODR & ~DATA_MASK1) \
        | (((val & 0x04) ? 0x20 : 0) | ((val & 0x08) ? 0x10 : 0) \
        | ((val & 0x10) ? 0x08 : 0) | ((val & 0x20) ? 0x04 : 0) \
        | ((val & 0x40) ? 0x40 : 0) | ((val & 0x80) ? 0x80 : 0)); \
} while (0)

// Set data direction to output
#define SET_DATA_DIR_OUT() do { \
    DATA_PORT3->PDR |= DATA_MASK3; \
    DATA_PORT1->PDR |= DATA_MASK1; \
} while (0)

// Set control direction to output
#define SET_CONTROL_DIR_OUT() do { \
    RD_PORT->PDR |= (1 << RD_PIN); \
    WR_PORT->PDR |= (1 << WR_PIN); \
    CD_PORT->PDR |= (1 << CD_PIN); \
    CS_PORT->PDR |= (1 << CS_PIN); \
    RESET_PORT->PDR |= (1 << RESET_PIN); \
} while (0)

#define PIN_LOW(port, pin)   ((port)->PODR &= ~(1 << (pin)))
#define PIN_HIGH(port, pin)  ((port)->PODR |=  (1 << (pin)))
#define PIN_OUTPUT(port, pin) ((port)->PDR |= (1 << (pin)))



#elif defined(ARDUINO_UNOR4_WIFI)
// Data pins: D8 (P304, P3.4), D9 (P303, P3.3), D2 (P104, P1.4), D3 (P105, P1.5), D4 (P106, P1.6), D5 (P107, P1.7), D6 (P111, P1.11), D7 (P112, P1.12)
// Control pins: A0 (P014, P0.14), A1 (P000, P0.0), A2 (P001, P0.1), A3 (P002, P0.2), A4 (P101, P1.1)

#define RD_PORT    R_PORT0
#define RD_PIN     14 // P014 (A0)
#define WR_PORT    R_PORT0
#define WR_PIN     0  // P000 (A1)
#define CD_PORT    R_PORT0
#define CD_PIN     1  // P001 (A2)
#define CS_PORT    R_PORT0
#define CS_PIN     2  // P002 (A3)
#define RESET_PORT R_PORT1
#define RESET_PIN  1  // P101 (A4)

// Data masks for port manipulation
#define DATA_PORT3 R_PORT3 // D8, D9
#define DATA_PORT1 R_PORT1 // D2-D7
#define DATA_MASK3 0x18    // P3.3 (D9), P3.4 (D8)
#define DATA_MASK1 ((1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<11)|(1<<12)) // P1.4 (D2), P1.5 (D3), P1.6 (D4), P1.7 (D5), P1.11 (D6), P1.12 (D7)

// Write 8 bits to the data bus
#define WRITE_8(val) do { \
    /* D8 (bit0) -> P3.4, D9 (bit1) -> P3.3 */ \
    DATA_PORT3->PODR = (DATA_PORT3->PODR & ~DATA_MASK3) \
        | (((val & 0x01) ? (1<<4) : 0) | ((val & 0x02) ? (1<<3) : 0)); \
    /* D2-D7: D2 (bit2) -> P1.4, D3 (bit3) -> P1.5, D4 (bit4) -> P1.6, D5 (bit5) -> P1.7, D6 (bit6) -> P1.11, D7 (bit7) -> P1.12 */ \
    DATA_PORT1->PODR = (DATA_PORT1->PODR & ~DATA_MASK1) \
        | (((val & 0x04) ? (1<<4) : 0) | ((val & 0x08) ? (1<<5) : 0) \
        | ((val & 0x10) ? (1<<6) : 0) | ((val & 0x20) ? (1<<7) : 0) \
        | ((val & 0x40) ? (1<<11) : 0) | ((val & 0x80) ? (1<<12) : 0)); \
} while (0)

// Set data direction to output
#define SET_DATA_DIR_OUT() do { \
    DATA_PORT3->PDR |= DATA_MASK3; \
    DATA_PORT1->PDR |= DATA_MASK1; \
} while (0)

// Set control direction to output
#define SET_CONTROL_DIR_OUT() do { \
    RD_PORT->PDR |= (1 << RD_PIN); \
    WR_PORT->PDR |= (1 << WR_PIN); \
    CD_PORT->PDR |= (1 << CD_PIN); \
    CS_PORT->PDR |= (1 << CS_PIN); \
    RESET_PORT->PDR |= (1 << RESET_PIN); \
} while (0)

#define PIN_LOW(port, pin)   ((port)->PODR &= ~(1 << (pin)))
#define PIN_HIGH(port, pin)  ((port)->PODR |=  (1 << (pin)))
#define PIN_OUTPUT(port, pin) ((port)->PDR |= (1 << (pin)))

#else
// Fallback for other boards (e.g., Giga, etc.) using Arduino API
// Data pins: D0 (8), D1 (9), D2 (2), D3 (3), D4 (4), D5 (5), D6 (6), D7 (7)
// Control pins: RD (A0), WR (A1), RS (A2), CS (A3), RST (A4)
#define ARDUINO_API_USED

static const uint8_t dataPins[] = { D0_PIN, D1_PIN, D2_PIN, D3_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN };
#define WRITE_8(val)            \
do {                          \
digitalWrite(D0_PIN, (val >> 0) & 0x01);  \
digitalWrite(D1_PIN, (val >> 1) & 0x01);  \
digitalWrite(D2_PIN, (val >> 2) & 0x01);  \
digitalWrite(D3_PIN, (val >> 3) & 0x01);  \
digitalWrite(D4_PIN, (val >> 4) & 0x01);  \
digitalWrite(D5_PIN, (val >> 5) & 0x01);  \
digitalWrite(D6_PIN, (val >> 6) & 0x01);  \
digitalWrite(D7_PIN, (val >> 7) & 0x01);  \
} while (0)
#define SET_WR_LOW() digitalWrite(API_PIN_WR, LOW)
#define SET_WR_HIGH() digitalWrite(API_PIN_WR, HIGH)
#define SET_RS_LOW() digitalWrite(API_PIN_CD, LOW)
#define SET_RS_HIGH() digitalWrite(API_PIN_CD, HIGH)
#define SET_CS_LOW() digitalWrite(API_PIN_CS, LOW)
#define SET_CS_HIGH() digitalWrite(API_PIN_CS, HIGH)
#define SET_RD_HIGH() digitalWrite(API_PIN_RD, HIGH)
#define SET_RST_LOW() digitalWrite(API_PIN_RESET, LOW)
#define SET_RST_HIGH() digitalWrite(API_PIN_RESET, HIGH)
#define SET_DATA_DIR_OUT() do { \
  for (uint8_t i = 0; i < 8; i++) { pinMode(dataPins[i], OUTPUT); } \
} while(0)
#define SET_CONTROL_DIR_OUT() do { \
  pinMode(API_PIN_RD, OUTPUT); \
  pinMode(API_PIN_WR, OUTPUT); \
  pinMode(API_PIN_CD, OUTPUT); \
  pinMode(API_PIN_CS, OUTPUT); \
  pinMode(API_PIN_RESET, OUTPUT); \
} while(0)
#define PIN_LOW(p) digitalWrite(p, LOW)
#define PIN_HIGH(p) digitalWrite(p, HIGH)
#define PIN_OUTPUT(p) pinMode(p, OUTPUT)
#endif

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
  static uint16_t colorRGB(uint8_t r, uint8_t g, uint8_t b) {
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

// Short alias
using DIYables_TFT = DIYables_TFT_ILI9486_Shield;

#endif // DIYables_TFT_Shield_H