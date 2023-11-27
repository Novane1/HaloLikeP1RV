#pragma once
#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"
using namespace std;
class AudioManager
{
protected :
	int nbFile;
    vector<ALuint> buff;
    vector<ALuint> sourc;
    ALCdevice* device;
    ALCcontext* context;
public:
	AudioManager();
    void AddSong(const char* audioFilePath,float v);
    void destroy();
    void playSong(int i);
};

