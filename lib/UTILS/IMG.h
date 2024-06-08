#ifndef _IMG_h
#define _IMG_h

#include <FS.h>
#include "UTILS.h"

class ImgParser
{
    fs::File file;
    /*
        0 is raw
        2 is 2byte comp
        4 is 1byte comp
    */
    uint16_t mode;
    byte current = 0;
    byte cnt = 0;

public:
    ImgParser(fs::File _file) : file(_file) {}
    Vec2 ReadHeader();
    u_int16_t read();
};

#endif