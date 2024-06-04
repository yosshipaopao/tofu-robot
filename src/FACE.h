#ifndef _FACE_h
#define _FACE_h

#include <TFT_eSPI.h>
#include "SPRITE.h"

class FaceCtrl
{
    TFT_eSPI *tft;
    short cheek_state = -1;
    char* cheeks[1] = {"/img/cheek/00"};
    short eye_state = -1;
    char* eyes[13] = {
        "/img/eye/00",
        "/img/eye/01",
        "/img/eye/02",
        "/img/eye/03",
        "/img/eye/04",
        "/img/eye/05",
        "/img/eye/06",
        "/img/eye/07",
        "/img/eye/08",
        "/img/eye/09",
        "/img/eye/10",
        "/img/eye/11",
        "/img/eye/12"
    };
    short mouse_state = -1;
    char* mouses[13] = {
        "/img/mouse/00",
        "/img/mouse/01",
        "/img/mouse/02",
        "/img/mouse/03",
        "/img/mouse/04",
        "/img/mouse/05",
        "/img/mouse/06",
        "/img/mouse/07",
        "/img/mouse/08",
        "/img/mouse/09",
        "/img/mouse/10",
        "/img/mouse/11",
        "/img/mouse/12"
    };
    Sprite cheek;
    Sprite eye;
    Sprite mouth;

public:
    bool state = false;
    FaceCtrl(TFT_eSPI *_tft)
        : tft(_tft),
          cheek(Sprite(tft, Vec2(27, 22), Vec2(10, 198),1)),
          eye(Sprite(tft, Vec2(78, 96), Vec2(52, 120),13)),
          mouth(Sprite(tft, Vec2(60, 48), Vec2(130, 192),13)) {}
    void begin();
    void stop();
    void handle();
};
#endif