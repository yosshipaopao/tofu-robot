#ifndef _SPRITE_h
#define _SPRITE_h

#include <TFT_eSPI.h>
#include "FS.h"
#include <LittleFS.h>
#include "UTILS.h"

class Sprite
{

public:
    Sprite(TFT_eSPI *_tft, Vec2 _size, Vec2 _pos = Vec2(0, 0))
        : Spr(TFT_eSprite(_tft)), size(_size), pos(_pos) {}
    Vec2 size;
    Vec2 pos;
    TFT_eSprite Spr;
    void ready();
    void blank();
    void clear();
    void pushSprite(Vec2 _pos = Vec2(-1, -1));
    void drawBmp(char* filename,bool reverse=false);
    void draw(char *filename,bool both_reverse=false);
};

#endif