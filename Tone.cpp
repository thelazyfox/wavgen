#include "Tone.h"
#include <math.h>
#include <fstream>

using std::ofstream;
using std::ios;

Tone::Tone(int sampleRate, int bitsPerSample) : m_sampleRate(sampleRate), 
												m_bitsPerSample(bitsPerSample)
{
}

Tone::~Tone()
{
}

bool Tone::writeFile(string filename, float pitch, float duration)
{
	pcm_header header;
	ofstream fout(filename.c_str(), ios::out);
	
	int period = (int)((float)m_sampleRate/pitch);
	int sampleCount = (int)(duration * (float)m_sampleRate);
	int dataSize = sampleCount * (m_bitsPerSample/2);
	
	initHeader(&header);
	
	header.ChunkSize += uint32toLE(dataSize);
	header.SubChunk2Size = uint32toLE(dataSize);
	
	fout.write((char *)&header, sizeof(pcm_header));
	
	vector<int> samples = generateWave(period);
	
	int i, j;
	for(i=0,j=0;i < sampleCount;i++,j++) {
		if(j == period)
			j = 0;
		
		fout.put(samples[j]);
	}
	
	return true;
}

void Tone::initHeader(pcm_header *header)
{
/* Main Chunk */
	memcpy(&(header->ChunkID), "RIFF", 4);
	memcpy(&(header->Format),  "WAVE", 4);
	header->ChunkSize = uint32toLE(36);

/* FMT Chunk */
	memcpy(&(header->SubChunk1ID), "fmt ", 4);
	header->SubChunk1Size = uint32toLE(16);
	header->AudioFormat   = uint16toLE(1);
	header->NumChannels   = uint16toLE(1);
	header->SampleRate    = uint32toLE(m_sampleRate);
	header->ByteRate      = uint32toLE(m_sampleRate * (m_bitsPerSample/8));
	header->BlockAlign    = uint16toLE(m_bitsPerSample/8);
	header->BitsPerSample = uint16toLE(m_bitsPerSample);

/* DATA Chunk */
	memcpy(&(header->SubChunk2ID), "data", 4);
	header->SubChunk2Size = uint32toLE(0);

}

vector<int> Tone::generateWave(int period)
{
	vector<int> samples;
	for(int i = 0;i < period;i++) {
		samples.push_back(((sin((((double)i)*TWOPI)/(double)period) + 1.0) * 255.0)/2.0);
	}
	
	return samples;
}

uint32_t Tone::uint32toLE(unsigned int value)
{
	return value;
}

uint16_t Tone::uint16toLE(unsigned short value)
{
	return value;
}


