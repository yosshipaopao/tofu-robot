#include "AUDIO.h"

void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
    (void)cbData;
    Serial.printf("ID3 callback for: %s = '", type);

    if (isUnicode)
    {
        string += 2;
    }

    while (*string)
    {
        char a = *(string++);
        if (isUnicode)
        {
            string++;
        }
        Serial.printf("%c", a);
    }
    Serial.printf("'\n");
    Serial.flush();
}

void AudioCtrl::init()
{
    SPIFFS.begin();
}

void AudioCtrl::play(char *path, void (*callback)(void *cbData, const char *type, bool isUnicode, const char *string) = MDCallback)
{
    file = new AudioFileSourceSPIFFS(path);
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(callback, (void *)"ID3TAG");
    out = new AudioOutputI2S(0, AudioOutputI2S::INTERNAL_DAC);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
}

bool AudioCtrl::isRunning()
{
    return mp3->isRunning();
}

void AudioCtrl::handle()
{
    if (!mp3->loop())
        mp3->stop();
}