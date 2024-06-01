#include "SPRITE.h"

void Sprite::ready()
{
    Spr.setColorDepth(8);
    Spr.setTextColor(TFT_BLACK);
    Spr.createSprite(size.x, size.y);
    blank();
}

void Sprite::blank()
{
    Spr.fillSprite(TFT_TRANSPARENT);
}

void Sprite::clear()
{
    Spr.deleteSprite();
}

void Sprite::pushSprite(Vec2 _pos)
{
    if (_pos == Vec2(-1, -1))
        _pos = pos;

    Spr.pushSprite(_pos.x, _pos.y, TFT_TRANSPARENT);
}