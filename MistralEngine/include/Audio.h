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

using namespace std;

class Audio {//There will be only an Audio object for the entire game, which will contain all buffers(sound effects)
public:
	Audio();

	int loadSound(const char* wavFile);
	void setListenerData(float x, float y, float z);


	//load wav file functions:
	bool isBigEndian();
	int convertToInt(char* buffer, int len);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

	~Audio();


private:
	ALCdevice* m_device;
	ALCcontext* m_context;

	list<unsigned int> m_listBuffers;

};