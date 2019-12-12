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

class AudioSource {//There will be an AudioSource object for every sound that we want to put (bulletSound, spaceshipMotorSound, etc)
public:
	AudioSource() {
		alGenSources(1, &sourceID);	//inicializar el bufferID del audio como lo inicializo aqui
		alSourcef(sourceID, AL_GAIN, 1);
		alSourcef(sourceID, AL_PITCH, 1);
		alSource3f(sourceID, AL_POSITION, 0, 0, 0);

	}

	void playSound(unsigned int bufferid) {
		stop();
		alSourcei(sourceID, AL_BUFFER, bufferid);
		alSourcePlay(sourceID);
	}

	void setVolume(float volume) {
		alSourcef(sourceID, AL_GAIN, volume);
	}

	void setPosition(float x, float y, float z) {
		alSource3f(sourceID, AL_POSITION, x, y, z);
	}

	void setVelocity(float x, float y, float z) {
		alSource3f(sourceID, AL_VELOCITY, x, y, z);
	}

	void setLooping(bool loop) {
		alSourcei(sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	void pause() {
		alSourcePause(sourceID);
	}


	void continuePlaying() {
		alSourcePlay(sourceID);
	}


	void stop() {
		alSourceStop(sourceID);
	}


	~AudioSource() {
		/*ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);*/
		stop();
		alDeleteSources(1, &sourceID);
	}

private:
	unsigned int sourceID;


};