#ifndef _SCREEN_h
#define _SCREEN_h

#include <SPI.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "UTILS.h"

class ScreenCtrl
{
    const int IRQ;
    const int MOSI;
    const int MISO;
    const int CLK;
    const int CS;

    SPIClass touchscreenSPI = SPIClass(VSPI);
    XPT2046_Touchscreen touchscreen;

public:
    const int WIDTH;
    const int HEIGHT;
    TFT_eSPI tft = TFT_eSPI();
    ScreenCtrl(int _irq, int _mosi, int _miso, int _clk, int _cs, int _width, int _height)
        : IRQ(_irq), MOSI(_mosi), MISO(_miso), CLK(_clk), CS(_cs), WIDTH(_width), HEIGHT(_height), touchscreen(_cs, _irq) {}
    void init();
    bool touched();
    Vec3 getPoint();

    // Scene Functions
    void drawBG(const unsigned short *img);
};

#endif