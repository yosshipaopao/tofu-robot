#include "FACE.h"

void FaceCtrl::begin()
{
    tft->fillScreen(TFT_WHITE);
    cheek.init(cheeks);
    eye.init(eyes);
    mouth.init(mouses);
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
    cheek.draw(random(-1, 1), random(-1, 1));
    eye.draw(random(0, 13), random(0, 13));
    mouth.draw(random(0, 13));
}