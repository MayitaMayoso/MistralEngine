#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

#include <al.h>
#include <alc.h>
#include <efx.h>
#include <efx-creative.h>
#include <EFX-Util.h>
#include <Xram.h>

class AudioSource {//There will be an AudioSource object for every object that we want to put sound on (bullet, enemy, spaceship, etc)
public:
	AudioSource() {
		alGenSources(1, &sourceID);	//inicializar el bufferID del audio como lo inicializo aqui
		alSourcef(sourceID, AL_GAIN, 1);
		alSourcef(sourceID, AL_PITCH, 1);
		alSource3f(sourceID, AL_POSITION, 0, 0, 0);

	}

	void playSound(unsigned int bufferid) {
		alSourcei(sourceID, AL_BUFFER, bufferid);
		alSourcePlay(sourceID);
	}

	~AudioSource() {
		/*ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);*/
		alDeleteSources(1, &sourceID);
	}

private:
	unsigned int sourceID;


};