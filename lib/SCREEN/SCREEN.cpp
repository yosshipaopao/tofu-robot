#include "SCREEN.h"

void ScreenCtrl::init()
{
    touchscreenSPI.begin(CLK, MISO, MOSI, CS);
    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(1);

    tft.init();
    tft.setRotation(1);
    tft.setTextColor(TFT_BLACK);
}

bool ScreenCtrl::touched()
{
    return touchscreen.tirqTouched() && touchscreen.touched();
}

Vec3 ScreenCtrl::getPoint()
{
    TS_Point p = touchscreen.getPoint();
    int x = map(p.x, 3900, 300, 0, WIDTH);
    int y = map(p.y, 3800, 240, 0, HEIGHT);
    int z = p.z;
    Vec3 point(x, y, z);
    return point;
}

void ScreenCtrl::drawBG(const unsigned short *img)
{
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, 320, 240, img);
}