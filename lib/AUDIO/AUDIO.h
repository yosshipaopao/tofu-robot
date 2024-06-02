#ifndef _AUDIO_h
#define _AUDIO_h

#include "FS.h"
#include <LittleFS.h>
#include "AudioFileSourceLittleFS.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

class AudioCtrl
{
public:
    AudioGeneratorMP3 *mp3;
    AudioFileSourceLittleFS *file;
    AudioOutputI2S *out;
    void init();
    void play(char *path);
    bool isRunning();
    void handle();
};

#endif