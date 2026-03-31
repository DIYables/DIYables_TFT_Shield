## TFT LCD Display Library for Arduino to work with DIYables TFT LCD Shield - DIYables_TFT_Shield
This Arduino library provides an easy-to-use interface for the [DIYables TFT LCD Display Shield](https://www.amazon.com/dp/B0DLMV7NTK).  
It enables fast and reliable graphics, text, and image rendering on your TFT shield.
* Fully extends the Adafruit GFX library, giving you access to all standard graphics and text functions.
* Adds optimized support for drawing shapes, displaying images, and rendering text specifically for the DIYables TFT LCD Display Shield.
* Compatible with a wide range of Arduino boards, including Uno R3, Uno R4 WiFi/Minima, Mega, Giga, Due, and more.

With this library, you can easily create colorful, high-resolution graphical interfaces for your Arduino projects using the DIYables TFT LCD Display Shield.

![DIYables TFT LCD Display](https://diyables.io/images/products/tft-lcd-display-shield-for-arduino-uno-mega.jpg)



Product Link
----------------------------
* [TFT LCD Display](https://diyables.io/products/3.5-inch-color-tft-lcd-display-screen-module-320x480-non-touch-for-arduino-uno-and-mega-ili9486-8-bit-parallel-interface)
* [Amazon Link](https://www.amazon.com/dp/B0DLMV7NTK)



Features  
----------------------------  
* Works with all hardware platforms, including Arduino Uno R3, Arduino Uno R4 WiFi/Minima, Arduino Mega, Arduino Giga, Arduino Due...



Available Examples
----------------------------
* **DrawImage.ino**: Demonstrates how to display a bitmap image stored in program memory (flash) directly on the TFT screen.
* **DrawImageSDcard.ino**: Shows how to load and display an image from an SD card onto the TFT display.
* **DrawShapes.ino**: Illustrates drawing various geometric shapes (such as circles, rectangles, triangles, and more) on the TFT screen using the library’s graphics functions.
* **ShowTextAndNumber.ino**: Demonstrates how to display text strings and numbers in different fonts, sizes, and colors on the TFT display.
* **UseExternalFont.ino**: Shows how to use and display external (custom) fonts on the TFT screen for enhanced text appearance.



Tutorials
----------------------------
* [Arduino - TFT LCD Display](https://arduinogetstarted.com/tutorials/arduino-tft-lcd-display)
* [Arduino UNO R4 - TFT LCD Display](https://newbiely.com/tutorials/arduino-uno-r4/arduino-uno-r4-tft-lcd-display)



References
----------------------------
* [DIYables_TFT_Shield Library Reference](https://arduinogetstarted.com/reference/library/diyables-tft-display-library)


Supported and Tested Hardware
----------------------------

| Board                   | Tested | Mode                      | Speed     |
|-------------------------|:------:|---------------------------|-----------|
| Arduino Uno R3          |   ✅   | Direct register access    | Very fast |
| [DIYables STEM V3 *(works like Arduino Uno R3)*](https://diyables.io/products/diyables-stem-v3-fully-compatible-with-arduino-uno-r3) |   ✅   | Direct register access    | Very fast |
| Arduino Uno R4 WiFi     |   ✅   | Direct register access    | Very fast |
| [DIYables STEM V4 IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4-iot-fully-compatible-with-arduino-uno-r4-wifi) |   ✅   | Direct register access    | Very fast |
| [DIYables STEM V4B IoT *(works like Arduino Uno R4 WiFi)*](https://diyables.io/products/diyables-stem-v4b-iot-development-board-compatible-with-arduino-uno-r4-wifi-ra4m1-32-bit-arm-cortex-m4-with-esp32-s3-wifi-bluetooth-usb-c-for-learning-prototyping-education) |   ✅   | Direct register access    | Very fast |
| Arduino Uno R4 Minima   |   ✅   | Direct register access    | Very fast |
| [DIYables STEM V4 Edu *(works like Arduino Uno R4 Minima)*](https://diyables.io/stem-v4-edu) |   ✅   | Direct register access    | Very fast |
| Arduino Mega            |   ✅   | Direct register access    | Very fast |
| [DIYables MEGA2560 R3 *(works like Arduino Mega 2560 Rev3)*](https://diyables.io/atmega2560-board) |   ✅   | Direct register access    | Very fast |
| Arduino Due             |   ✅   | Direct register access    | Very fast |
| Arduino Giga            |   ✅   | Direct register access    | Very fast |
| [DIYables ESP32 S3, Uno-form factor](https://diyables.io/products/esp32-s3-development-board-with-esp32-s3-wroom-1-n16r8-wifi-bluetooth-uno-compatible-form-factor-works-with-arduino-ide) |   ✅   | Direct register access    | Very fast |
| Other boards            |   —    | Arduino API (digitalWrite)| Slower    |

**Using with Non-Standard Boards**: If your board does not use the standard Uno R3 pin naming (D2–D9 for data, A0–A4 for control), use the custom pin constructor:

```cpp
DIYables_TFT_ILI9486_Shield tft(LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7,
                                 LCD_RD, LCD_WR, LCD_CD, LCD_CS, LCD_RST);
```

Replace each parameter with the actual pin number on your board, using the following mapping:

| Parameter | Shield Pin | Default Pin (Uno R3) | Description        |
|-----------|------------|----------------------|--------------------|
| LCD_D0    | D8         | 8                    | Data bit 0         |
| LCD_D1    | D9         | 9                    | Data bit 1         |
| LCD_D2    | D2         | 2                    | Data bit 2         |
| LCD_D3    | D3         | 3                    | Data bit 3         |
| LCD_D4    | D4         | 4                    | Data bit 4         |
| LCD_D5    | D5         | 5                    | Data bit 5         |
| LCD_D6    | D6         | 6                    | Data bit 6         |
| LCD_D7    | D7         | 7                    | Data bit 7         |
| LCD_RD    | A0         | A0                   | Read strobe        |
| LCD_WR    | A1         | A1                   | Write strobe       |
| LCD_CD    | A2         | A2                   | Command/Data       |
| LCD_CS    | A3         | A3                   | Chip Select        |
| LCD_RST   | A4         | A4                   | Reset              |

This constructor uses `digitalWrite` (Arduino API) so it works on any board.

**Note**: This library is designed for the [DIYables 3.5 Inch ILI9486 TFT LCD Display Screen Shield (non-touch)](https://www.amazon.com/dp/B0DLMV7NTK). If you're using the [DIYables 3.5 Inch ILI9488 TFT LCD Display Screen Shield (with touch)](https://www.amazon.com/dp/B0DQ3NQ3LW), please use the [DIYables TFT Touch Shield Library](https://github.com/DIYables/DIYables_TFT_Touch_Shield) instead.

