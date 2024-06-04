#include <Arduino.h>

// libraries
#include "AUDIO.h"
#include "SCREEN.h"
#include "FACE.h"

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

////////////////////////////////
//                            //
//          Main Code         //
//                            //
////////////////////////////////

TaskHandle_t thp[1];

void Core0a(void *args);
void printTouchToDisplay(int touchX, int touchY, int touchZ);

FaceCtrl face_ctrl(&screen_ctrl.tft);

void setup()
{
  Serial.begin(115200);
  if (!LittleFS.begin())
  {
    Serial.println("File System Mount Failed");
    while (1)
      yield();
  }
  screen_ctrl.init();
  audio_ctrl.init();
  audio_ctrl.play((char *)"/audio-test.mp3");
  face_ctrl.begin();

  xTaskCreatePinnedToCore(Core0a, "Core0a", 4096, NULL, 3, &thp[0], 0);
  delay(400);
}

void loop()
{
  if (screen_ctrl.touched())
  {
    Vec3 p = screen_ctrl.getPoint();

    Serial.printf("x: %3d , y: %3d , Pressure: %4d \n", p.x, p.y, p.z);
    if (p.x < 50 && p.y < 50)
    {
      if (face_ctrl.state)
        face_ctrl.stop();
      else
        face_ctrl.begin();
    }
    face_ctrl.handle();
    delay(100);
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