#include "Audio.h"


Audio::Audio() {
	//Initialization
	m_device = alcOpenDevice(NULL);

	if (m_device) {
		m_context = alcCreateContext(m_device, NULL);
		alcMakeContextCurrent(m_context);
	}

}



int Audio::loadSound(const char* wavFile) {
	//Generate new buffer
	unsigned int m_buffer;
	alGenBuffers(1, &m_buffer);
	//m_listBuffers.push_back(m_buffer);

	//Load .wav file
	int channel, sampleRate, bps, size;
	char* data = loadWAV(wavFile, channel, sampleRate, bps, size);


	unsigned int format;

	if (channel == 1) {
		if (bps == 8)
			format = AL_FORMAT_MONO8;
		else format = AL_FORMAT_MONO16;
	}
	else {
		if (bps == 8)
			format = AL_FORMAT_STEREO8;
		else format = AL_FORMAT_STEREO16;
	}

	//Copy .wav data into AL buffer
	alBufferData(m_buffer, format, data, size, sampleRate);

	return m_buffer;
}



void Audio::setListenerData(float x, float y, float z) {
	alListener3f(AL_POSITION, x, y, z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
}



Audio::~Audio() {
	while (!m_listBuffers.empty()) {
		alDeleteBuffers(1, &m_listBuffers.back());
	}
}


bool Audio::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int Audio::convertToInt(char* buffer, int len)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* Audio::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "this is not a valid WAVE file" << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);      //data
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);
	char* data = new char[size];
	in.read(data, size);
	return data;
}

