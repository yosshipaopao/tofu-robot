#ifndef _SPRITE_h
#define _SPRITE_h

#include <TFT_eSPI.h>
#include "FS.h"
#include "UTILS.h"

#include <LittleFS.h>
#define FileSys LittleFS

class Sprite
{
    u_short file_len = 0;
    char *files[20];

public:
    Sprite(TFT_eSPI *_tft, Vec2 _size, Vec2 _pos, u_short _file_len)
        : Spr(TFT_eSprite(_tft)), size(_size), pos(_pos), file_len(_file_len) {}
    Vec2 size;
    Vec2 pos;
    TFT_eSprite Spr;
    void init(char *_files[]);
    void ready();
    void blank();
    void clear();
    void pushSprite(Vec2 _pos = Vec2(-1, -1),bool invert=false);
    void drawBmp(char *filename, bool reverse = false);
    void draw(short id, short id_2 = -2);
};

#endif