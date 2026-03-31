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
// Data pins: D8=PC22, D9=PC21, D2=PB25, D3=PC28, D4=PC26, D5=PC25, D6=PC24, D7=PC23
// Control pins: A0(RD)=PA16, A1(WR)=PA24, A2(CD)=PA23, A3(CS)=PA22, A4(RST)=PA6
#define RD_PORT    PIOA
#define RD_PIN     16
#define WR_PORT    PIOA
#define WR_PIN     24
#define CD_PORT    PIOA
#define CD_PIN     23
#define CS_PORT    PIOA
#define CS_PIN     22
#define RESET_PORT PIOA
#define RESET_PIN  6

#define DUE_BMASK (1UL<<25)
#define DUE_CMASK ((1UL<<21)|(1UL<<22)|(1UL<<23)|(1UL<<24)|(1UL<<25)|(1UL<<26)|(1UL<<28))
#define WRITE_8(val) do { \
  PIOB->PIO_CODR = DUE_BMASK; \
  PIOC->PIO_CODR = DUE_CMASK; \
  PIOB->PIO_SODR = (((val) & (1<<2)) ? (1UL<<25) : 0); \
  PIOC->PIO_SODR = \
    (((val) & (1<<0)) ? (1UL<<22) : 0) | \
    (((val) & (1<<1)) ? (1UL<<21) : 0) | \
    (((val) & (1<<3)) ? (1UL<<28) : 0) | \
    (((val) & (1<<4)) ? (1UL<<26) : 0) | \
    (((val) & (1<<5)) ? (1UL<<25) : 0) | \
    (((val) & (1<<6)) ? (1UL<<24) : 0) | \
    (((val) & (1<<7)) ? (1UL<<23) : 0); \
} while(0)
#define SET_DATA_DIR_OUT() do { \
  PIOB->PIO_OER = DUE_BMASK; \
  PIOC->PIO_OER = DUE_CMASK; \
} while(0)
#define SET_CONTROL_DIR_OUT() do { \
  PIOA->PIO_OER = (1UL<<16)|(1UL<<24)|(1UL<<23)|(1UL<<22)|(1UL<<6); \
} while(0)
#define PIN_LOW(p, b) (p)->PIO_CODR = (1UL << (b))
#define PIN_HIGH(p, b) (p)->PIO_SODR = (1UL << (b))
#define PIN_OUTPUT(p, b) (p)->PIO_OER = (1UL << (b))


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

#elif defined(CONFIG_IDF_TARGET_ESP32S3)
// For this board: https://diyables.io/products/esp32-s3-development-board-with-esp32-s3-wroom-1-n16r8-wifi-bluetooth-uno-compatible-form-factor-works-with-arduino-ide
// --- ESP32-S3 Uno Port Manipulation ---
#include "soc/gpio_reg.h"
#include "soc/gpio_struct.h"

// Data pins mapping for ESP32-S3 Uno
#undef D0_PIN
#undef D1_PIN
#undef D2_PIN
#undef D3_PIN
#undef D4_PIN
#undef D5_PIN
#undef D6_PIN
#undef D7_PIN
#define D0_PIN 21
#define D1_PIN 46
#define D2_PIN 18
#define D3_PIN 17
#define D4_PIN 19
#define D5_PIN 20
#define D6_PIN 3
#define D7_PIN 14

// Control pins mapping
#define RD_PORT      0 // Virtual port identifier
#define RD_PIN       2 // IO2 (A0)
#define WR_PORT      0
#define WR_PIN       1 // IO1 (A1)
#define CD_PORT      0
#define CD_PIN       7 // IO7 (A2)
#define CS_PORT      0
#define CS_PIN       6 // IO6 (A3)
#define RESET_PORT   0
#define RESET_PIN    5 // IO5 (A4)

// Write 8 bits to the data bus using Fast Register Access
#define WRITE_8(val) do { \
    uint32_t set0 = 0, clr0 = 0; \
    uint32_t set1 = 0, clr1 = 0; \
    if ((val) & 0x01) set0 |= (1UL << 21); else clr0 |= (1UL << 21); \
    if ((val) & 0x02) set1 |= (1UL << (46 - 32)); else clr1 |= (1UL << (46 - 32)); \
    if ((val) & 0x04) set0 |= (1UL << 18); else clr0 |= (1UL << 18); \
    if ((val) & 0x08) set0 |= (1UL << 17); else clr0 |= (1UL << 17); \
    if ((val) & 0x10) set0 |= (1UL << 19); else clr0 |= (1UL << 19); \
    if ((val) & 0x20) set0 |= (1UL << 20); else clr0 |= (1UL << 20); \
    if ((val) & 0x40) set0 |= (1UL << 3);  else clr0 |= (1UL << 3);  \
    if ((val) & 0x80) set0 |= (1UL << 14); else clr0 |= (1UL << 14); \
    REG_WRITE(GPIO_OUT_W1TS_REG, set0); \
    REG_WRITE(GPIO_OUT_W1TC_REG, clr0); \
    REG_WRITE(GPIO_OUT1_W1TS_REG, set1); \
    REG_WRITE(GPIO_OUT1_W1TC_REG, clr1); \
} while (0)

// Set data direction to output
#define SET_DATA_DIR_OUT() do { \
    static const uint8_t d_pins[] = {D0_PIN, D1_PIN, D2_PIN, D3_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN}; \
    for (uint8_t i = 0; i < 8; i++) { pinMode(d_pins[i], OUTPUT); } \
} while (0)

// Set control direction to output
#define SET_CONTROL_DIR_OUT() do { \
    pinMode(RD_PIN, OUTPUT); \
    pinMode(WR_PIN, OUTPUT); \
    pinMode(CD_PIN, OUTPUT); \
    pinMode(CS_PIN, OUTPUT); \
    pinMode(RESET_PIN, OUTPUT); \
} while (0)

// Standardized Bit-Level control macros
#define PIN_LOW(port, pin) do { \
    if ((pin) < 32) REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << (pin))); \
    else REG_WRITE(GPIO_OUT1_W1TC_REG, (1UL << ((pin) - 32))); \
} while (0)

#define PIN_HIGH(port, pin) do { \
    if ((pin) < 32) REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << (pin))); \
    else REG_WRITE(GPIO_OUT1_W1TS_REG, (1UL << ((pin) - 32))); \
} while (0)

#define PIN_OUTPUT(port, pin) pinMode(pin, OUTPUT)

#elif defined(ARDUINO_GIGA)
// Arduino Giga R1 WiFi (STM32H747XI)
// Data pins: D8=PB8, D9=PB9, D2=PA3, D3=PA2, D4=PJ8, D5=PA7, D6=PD13, D7=PB4
// Control pins: A0(RD)=PC4, A1(WR)=PC5, A2(CD)=PB0, A3(CS)=PB1, A4(RST)=PC3

#define RD_PORT    GPIOC
#define RD_PIN     4
#define WR_PORT    GPIOC
#define WR_PIN     5
#define CD_PORT    GPIOB
#define CD_PIN     0
#define CS_PORT    GPIOB
#define CS_PIN     1
#define RESET_PORT GPIOC
#define RESET_PIN  3

// Data pins spread across GPIOA (pins 2,3,7), GPIOB (pins 4,8,9), GPIOD (pin 13), GPIOJ (pin 8)
// GPIOA: bit2=PA3(D3), bit3=PA2(D2 mapped to bit2 in val but PA3), bit5=PA7(D5)
//   Actually: D2(val bit2)->PA3, D3(val bit3)->PA2, D5(val bit5)->PA7
// GPIOB: D8(val bit0)->PB8, D9(val bit1)->PB9, D7(val bit7)->PB4
// GPIOD: D6(val bit6)->PD13
// GPIOJ: D4(val bit4)->PJ8

#define GIGA_AMASK ((1UL<<2)|(1UL<<3)|(1UL<<7))          // PA2, PA3, PA7
#define GIGA_BMASK ((1UL<<4)|(1UL<<8)|(1UL<<9))          // PB4, PB8, PB9
#define GIGA_DMASK (1UL<<13)                               // PD13
#define GIGA_JMASK (1UL<<8)                                // PJ8

#define WRITE_8(val) do { \
    uint32_t a_set = 0, a_clr = 0; \
    uint32_t b_set = 0, b_clr = 0; \
    uint32_t d_set = 0, d_clr = 0; \
    uint32_t j_set = 0, j_clr = 0; \
    /* bit0 (D8) -> PB8 */ \
    if ((val) & 0x01) b_set |= (1UL<<8);  else b_clr |= (1UL<<8);  \
    /* bit1 (D9) -> PB9 */ \
    if ((val) & 0x02) b_set |= (1UL<<9);  else b_clr |= (1UL<<9);  \
    /* bit2 (D2) -> PA3 */ \
    if ((val) & 0x04) a_set |= (1UL<<3);  else a_clr |= (1UL<<3);  \
    /* bit3 (D3) -> PA2 */ \
    if ((val) & 0x08) a_set |= (1UL<<2);  else a_clr |= (1UL<<2);  \
    /* bit4 (D4) -> PJ8 */ \
    if ((val) & 0x10) j_set |= (1UL<<8);  else j_clr |= (1UL<<8);  \
    /* bit5 (D5) -> PA7 */ \
    if ((val) & 0x20) a_set |= (1UL<<7);  else a_clr |= (1UL<<7);  \
    /* bit6 (D6) -> PD13 */ \
    if ((val) & 0x40) d_set |= (1UL<<13); else d_clr |= (1UL<<13); \
    /* bit7 (D7) -> PB4 */ \
    if ((val) & 0x80) b_set |= (1UL<<4);  else b_clr |= (1UL<<4);  \
    GPIOA->BSRR = a_set | (a_clr << 16); \
    GPIOB->BSRR = b_set | (b_clr << 16); \
    GPIOD->BSRR = d_set | (d_clr << 16); \
    GPIOJ->BSRR = j_set | (j_clr << 16); \
} while(0)

#define SET_DATA_DIR_OUT() do { \
    pinMode(8, OUTPUT); pinMode(9, OUTPUT); \
    pinMode(2, OUTPUT); pinMode(3, OUTPUT); \
    pinMode(4, OUTPUT); pinMode(5, OUTPUT); \
    pinMode(6, OUTPUT); pinMode(7, OUTPUT); \
} while(0)

#define SET_CONTROL_DIR_OUT() do { \
    pinMode(A0, OUTPUT); pinMode(A1, OUTPUT); \
    pinMode(A2, OUTPUT); pinMode(A3, OUTPUT); \
    pinMode(A4, OUTPUT); \
} while(0)

#define PIN_LOW(port, pin)   (port)->BSRR = (1UL << ((pin) + 16))
#define PIN_HIGH(port, pin)  (port)->BSRR = (1UL << (pin))
#define PIN_OUTPUT(port, pin) /* handled by SET_*_DIR_OUT */

#else
// Fallback for other boards using Arduino API
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
  DIYables_TFT_ILI9486_Shield(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                               uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                               uint8_t rd, uint8_t wr, uint8_t cd, uint8_t cs, uint8_t rst);
  void begin();
  void fillScreen(uint16_t color) override;
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
  void setRotation(uint8_t r) override;
  void invertDisplay(bool i) override;
  void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
  void pushColors(uint16_t *data, uint32_t len);
  void setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

  /**
   * Convert 8-bit R,G,B to 16-bit 565 color format.
   */
  static uint16_t colorRGB(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  }

  void drawPixel(int16_t x, int16_t y, uint16_t color) override;

protected:
  uint8_t _d[8];
  uint8_t _rd, _wr, _cd, _cs, _rst;
  bool _useAPI;

  inline void reset();
  inline void writeCommand(uint8_t cmd);
  inline void writeData(uint8_t data);
  inline void write8(uint8_t val);
  inline void writeBus(uint8_t val);
  inline void pulseWR();
  void setWriteDir();
  void writeData16(uint16_t data, uint32_t count);
};

// Short alias
using DIYables_TFT = DIYables_TFT_ILI9486_Shield;

#endif // DIYables_TFT_Shield_H