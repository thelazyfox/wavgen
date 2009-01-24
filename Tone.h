#ifndef __TONE_H__
#define __TONE_H__

#include <stdint.h>
#include <vector>
#include <string>
#include "wav.h"

using std::vector;
using std::string;

#define TWOPI 6.28318531

class Tone
{
public:
	Tone(int sampleRate, int bitsPerSample);
	~Tone();

	bool writeFile(string filename, float pitch, float duration);

	vector<int> generateWave(int period);

private:
	int m_sampleRate;
	int m_bitsPerSample;

	void initHeader(pcm_header *header);

	uint32_t uint32toLE(unsigned int value);
	uint16_t uint16toLE(unsigned short value);
};

#endif
