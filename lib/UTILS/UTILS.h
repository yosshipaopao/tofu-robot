#ifndef _UTILS_h
#define _UTILS_h

class Vec2
{
public:
    bool operator==(Vec2 a);
    Vec2(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};

class Vec3
{
public:
    Vec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    int x;
    int y;
    int z;
};

#endif