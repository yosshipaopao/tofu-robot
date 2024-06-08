#include "SPRITE.h"

void Sprite::init(char *_files[])
{
  Spr.setColorDepth(8);
  Spr.setTextColor(TFT_BLACK);
  for (short i = 0; i < file_len; i++)
  {
    files[i] = _files[i];
  }
}

void Sprite::ready()
{
  Spr.createSprite(size.x, size.y);
  Spr.setPivot(320 - pos.x, pos.y + size.y);
  blank();
}

void Sprite::blank()
{
  Spr.fillSprite(TFT_WHITE);
}

void Sprite::clear()
{
  Spr.deleteSprite();
}

void Sprite::pushSprite(Vec2 _pos, bool invert)
{
  if (_pos == Vec2(-1, -1))
    _pos = pos;

  Spr.pushSprite(invert ? 320 - _pos.x - size.x : pos.x, _pos.y);
}

// drawBmp

uint16_t byteTo565(byte a)
{
  return (a >> 3) + ((a >> 2) << 5) + ((a >> 3) << 11);
}

void Sprite::drawBmp(char *filename, bool reverse)
{
  fs::File rawFile;
  rawFile = FileSys.open(filename);
  if (!rawFile)
  {
    Serial.print("File not found");
    return;
  }
  Serial.printf("file %s found !!!\n", filename);

  uint32_t startTime = millis();

  ImgParser img_parser(rawFile);

  uint16_t w, h;
  Vec2 tmp = img_parser.ReadHeader();
  Serial.println("Header Read");
  h = tmp.x;
  w = tmp.y;

  Serial.printf("h,w=%d,%d\n", h, w);

  for (uint16_t x = 0; x < h; x++)
  {
    for (uint16_t y = 0; y < w; y++)
    {
      Spr.drawPixel(reverse ? w - y - 1 : y, x, byteTo565((byte)img_parser.read()));
    }
  }
  rawFile.close();
  Serial.print("Loaded in ");
  Serial.print(millis() - startTime);
  Serial.println(" ms");
}

void Sprite::draw(short id, short id_2)
{
  if (id != -2)
  {
    if (id == -1)
      blank();
    else
      drawBmp(files[id]);
    pushSprite();
  }
  if (id_2 != -2)
  {
    if (id_2 == -1)
      blank();
    else
      drawBmp(files[id_2], true);
    pushSprite(Vec2(-1, -1), true);
  }
}