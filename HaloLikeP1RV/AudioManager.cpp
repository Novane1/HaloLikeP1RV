#include "AudioManager.h"
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>
void checkALError(const char* message) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << message << ": OpenAL error - " << alGetString(error) << std::endl;
        exit(EXIT_FAILURE);
    }
}

AudioManager::AudioManager()
{
    nbFile = 0;
    device = alcOpenDevice(nullptr);
    checkALError("Failed to open OpenAL device");

    context = alcCreateContext(device, nullptr);
    checkALError("Failed to create OpenAL context");

    alcMakeContextCurrent(context);
}

void AudioManager::AddSong(const char* audioFilePath, float v)
{
    nbFile++;

    ALuint buffer, source;

    buff.push_back(0); // Reserve a space in the vector
    sourc.push_back(0);


    alGenBuffers(1, &buffer);
    checkALError("Failed to generate OpenAL buffer");
    buff[nbFile - 1] = buffer; // Assign the generated buffer to the vector

    alGenSources(1, &source);
    checkALError("Failed to generate OpenAL source");
    sourc[nbFile - 1] = source; // Assign the generated source to the vector
   




    std::ifstream audioFile(audioFilePath, std::ios::binary | std::ios::ate);

    if (!audioFile.is_open()) {
        std::cerr << "Failed to open audio file" << std::endl;
       
    }

    std::streamsize fileSize = audioFile.tellg();
    audioFile.seekg(0, std::ios::beg);

    std::vector<char> audioData(fileSize);
    if (!audioFile.read(audioData.data(), fileSize)) {
        std::cerr << "Failed to read audio file" << std::endl;
        
    }

    // Set the buffer data
    alBufferData(buffer, AL_FORMAT_STEREO16, audioData.data(), fileSize, 48000);  // Adjust sample rate as needed
    checkALError("Failed to set buffer data");

    // Attach the buffer to the source
    alSourcei(source, AL_BUFFER, buffer);
    checkALError("Failed to attach buffer to source");

    // Set the volume of the sound source to 0.5 (you can use any value between 0.0 and 1.0)
    alSourcef(source, AL_GAIN, v);
    checkALError("Failed to attach buffer to volume");
    
}

void AudioManager::destroy()
{
    for (int i = 0; i < nbFile; i++)
    {
        alDeleteSources(i + 1, &sourc[i]);
        alDeleteBuffers(i + 1, &buff[i]);

    }



    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
void AudioManager::playSong(int i)
{

    alSourcePlay(sourc[i]);
    checkALError("Failed to play source");


    ALint sourceState;

    alGetSourcei(sourc[i], AL_SOURCE_STATE, &sourceState);
}
