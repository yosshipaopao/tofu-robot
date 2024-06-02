#include "AUDIO.h"

void AudioCtrl::init()
{
    SPIFFS.begin();
    out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
    mp3 = new AudioGeneratorMP3();
}

void AudioCtrl::play(char *path)
{
    file = new AudioFileSourceSPIFFS(path);
    id3 = new AudioFileSourceID3(file);
    mp3->begin(id3, out);
}

bool AudioCtrl::isRunning()
{
    return mp3->isRunning();
}

void AudioCtrl::handle()
{
    if (isRunning())
        if (!mp3->loop())
            mp3->stop();
}