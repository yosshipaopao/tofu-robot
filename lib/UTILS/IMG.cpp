#include "IMG.h"

Vec2 ImgParser::ReadHeader()
{
    mode = file.read();
    uint16_t h = (file.read() >> 8) + file.read();
    uint16_t w = (file.read() >> 8) + file.read();
    return Vec2(h, w);
}

uint16_t ImgParser::read()
{
    if (mode == 0)
        return file.read();
    else if (mode == 2)
    {
        if (cnt == 0)
        {
            current = file.read();
            cnt = file.read() + 1;
        }
        cnt -= 1;
        return current;
    }
    else if (mode == 4)
    {
        if (cnt == 0)
        {
            byte tmp = file.read();
            current = (tmp >> 3) << 3;
            cnt = (tmp & 0b111) + 1;
        }
        cnt -= 1;
        return current;
    }
    return -1;
}