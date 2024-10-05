#ifndef _AUDIO_h
#define _AUDIO_h

#include "FS.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include <LittleFS.h>
#include "AudioFileSourceLittleFS.h"
#include "BluetoothA2DPSink.h"

class AudioCtrl
{
public:
    AudioGeneratorMP3 *mp3;
    AudioOutputI2S *out;
    AudioFileSourceLittleFS *file;

    void init();
    void play(char *path);
    bool isRunning();
    void handle();
};

#endif