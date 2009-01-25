#ifndef __TONE_H__
#define __TONE_H__

#include <stdint.h>
#include <vector>
#include <string>
#include "wav.h"
#include <fstream>

using std::vector;
using std::string;

#define TWOPI 6.28318531
#define DEFAULT_SAMPLE_RATE 44100
#define DEFAULT_BITS_PER_SAMPLE 16

class Tone
{
public:
	Tone(int sampleRate = DEFAULT_SAMPLE_RATE, int bitsPerSample = DEFAULT_BITS_PER_SAMPLE);
	~Tone();

	bool writeFile(string filename, float pitch, float duration);

private:
	int m_sampleRate;
	int m_bitsPerSample;

	void initHeader(pcm_header *header);
	
	vector<double>	generateWave(int period);
	void			scaleWave(vector<double> &wave, char *data);
	
	void writeSample(int value, std::ofstream &out);

	uint32_t uint32toLE(unsigned int value);
	uint16_t uint16toLE(unsigned short value);
	
	int16_t int16toLE(int value);
};

#endif
