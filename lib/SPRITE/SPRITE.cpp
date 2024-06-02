#include "SPRITE.h"

void Sprite::ready()
{
  Spr.setColorDepth(8);
  Spr.setTextColor(TFT_BLACK);
  Spr.setSwapBytes(true);
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

void Sprite::pushSprite(Vec2 _pos)
{
  if (_pos == Vec2(-1, -1))
    _pos = pos;

  Spr.pushSprite(_pos.x, _pos.y);
}

// drawBmp

uint16_t read16(fs::File &f)
{
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(fs::File &f)
{
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

void Sprite::drawBmp(char *filename, bool reverse)
{
  int x = 0, y = 0;
  fs::File bmpFS;
  bmpFS = LittleFS.open(filename, "r");
  if (!bmpFS)
  {
    Serial.print("File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t r, g, b;

  uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;

      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];

      for (row = 0; row < h; row++)
      {

        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t *bptr = lineBuffer;
        uint16_t *tptr = (uint16_t *)lineBuffer;
        // Convert 24 to 16-bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }

        // Push the pixel row to screen, pushImage will crop the line if needed
        // y is decremented as the BMP image is drawn bottom up
        Spr.pushImage(x, reverse ? h - 1 - (y--) : y--, w, 1, (uint16_t *)lineBuffer);
      }
      Serial.print("Loaded in ");
      Serial.print(millis() - startTime);
      Serial.println(" ms");
    }
    else
      Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}

void Sprite::draw(char *filename, bool both_reverse)
{
  if (filename == "")
  {
    blank();
    pushSprite();
    if (both_reverse)
      Spr.pushRotated(180);
  }
  else
  {
    drawBmp(filename);
    pushSprite();
    if (both_reverse)
    {
      drawBmp(filename, true);
      Spr.pushRotated(180);
    }
  }
}