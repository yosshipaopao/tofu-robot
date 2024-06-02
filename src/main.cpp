#include <Arduino.h>

// libraries
#include "AUDIO.h"
#include "SCREEN.h"
#include "SPRITE.h"

// Images
#include "img.h"

////////////////////////////////
//
//          Configs           //
//                            //
////////////////////////////////

// Touchscreen pins
#define XPT2046_IRQ 34  // T_IRQ
#define XPT2046_MOSI 32 // T_DIN
#define XPT2046_MISO 35 // T_OUT
#define XPT2046_CLK 22  // T_CLK
#define XPT2046_CS 33   // T_CS

ScreenCtrl screen_ctrl(XPT2046_IRQ, XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS, 320, 240);
AudioCtrl audio_ctrl;
Sprite TXT(screen_ctrl.tft, Vec2(320, 240));

////////////////////////////////
//                            //
//          Main Code         //
//                            //
////////////////////////////////

TaskHandle_t thp[1];

void Core0a(void *args);
void printTouchToDisplay(int touchX, int touchY, int touchZ);

void setup()
{
  screen_ctrl.init();
  audio_ctrl.init();
  audio_ctrl.play((char *)"/audio-test.mp3");

  xTaskCreatePinnedToCore(Core0a, "Core0a", 4096, NULL, 3, &thp[0], 0);

  // BG
  screen_ctrl.drawBG(img);

  // TXT
  TXT.ready();
  TXT.Spr.drawCentreString("TOUCH TO START", screen_ctrl.WIDTH / 2, screen_ctrl.HEIGHT / 2, 2);
  TXT.pushSprite();
  TXT.blank();

  Serial.begin(115200);
  delay(400);
}

void loop()
{
  if (screen_ctrl.touched())
  {
    Vec3 p = screen_ctrl.getPoint();

    Serial.printf("x: %3d , y: %3d , Pressure: %4d \n", p.x, p.y, p.z);
    printTouchToDisplay(p.x, p.y, p.z);
  }
}

void Core0a(void *args)
{
  while (1)
  {
    audio_ctrl.handle();
    delay(25);
  }
}

// Print Touchscreen info about X, Y and Pressure (Z) on the TFT Display
void printTouchToDisplay(int touchX, int touchY, int touchZ)
{
  // Clear TFT screen
  screen_ctrl.drawBG(img);
  TXT.blank();
  int centerX = screen_ctrl.WIDTH / 2;
  int textY = 80;

  String tempText = "X = " + String(touchX);
  TXT.Spr.drawCentreString(tempText, centerX, textY, 2);

  textY += 20;
  tempText = "Y = " + String(touchY);
  TXT.Spr.drawCentreString(tempText, centerX, textY, 2);

  textY += 20;
  tempText = "Pressure = " + String(touchZ);
  TXT.Spr.drawCentreString(tempText, centerX, textY, 2);

  TXT.Spr.drawPixel(touchX, touchY, TFT_RED);

  TXT.pushSprite();
}