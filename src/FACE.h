#ifndef _FACE_h
#define _FACE_h

#include <TFT_eSPI.h>
#include "SPRITE.h"

class FaceCtrl
{
    TFT_eSPI *tft;
    bool state = false;
    Sprite cheek;
    Sprite eye;
    Sprite mouth;

public:
    FaceCtrl(TFT_eSPI *_tft)
        : tft(_tft),
          cheek(Sprite(tft, Vec2(27, 22), Vec2(10, 198))),
          eye(Sprite(tft, Vec2(78, 96), Vec2(52, 120))),
          mouth(Sprite(tft, Vec2(60, 48), Vec2(130, 192))) {}
    void begin();
    void stop();
    void handle();
};
#endif