#include "FACE.h"

void FaceCtrl::begin()
{
    tft->fillScreen(TFT_WHITE);
    cheek.ready();
    eye.ready();
    mouth.ready();
    state = true;
}

void FaceCtrl::stop()
{
    cheek.clear();
    eye.clear();
    mouth.clear();
    tft->fillScreen(TFT_WHITE);
    state = false;
}

void FaceCtrl::handle()
{
    if (!state)
        return;
    cheek.draw("/cheek.bmp", true);
    eye.draw("/eye/eye_0000.bmp", true);
    mouth.draw("/mouse/mouse_0000.bmp");
}