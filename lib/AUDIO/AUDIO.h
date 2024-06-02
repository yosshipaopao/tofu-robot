#ifndef _AUDIO_h
#define _AUDIO_h

#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

class AudioCtrl
{
public:
    AudioGeneratorMP3 *mp3;
    AudioFileSourceSPIFFS *file;
    AudioOutputI2S *out;
    AudioFileSourceID3 *id3;
    void init();
    void play(char *path);
    bool isRunning();
    void handle();
};

#endif