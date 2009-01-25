#include "Tone.h"
#include <math.h>
#include <fstream>
#include <iostream>

using std::ofstream;
using std::ios;

Tone::Tone(int sampleRate, int bitsPerSample)
{
	if(sampleRate <= 0 || sampleRate > 192000)
		m_sampleRate = DEFAULT_SAMPLE_RATE;
	else
		m_sampleRate = sampleRate;
		
	if(bitsPerSample != 8 && bitsPerSample != 16)
		m_bitsPerSample = DEFAULT_BITS_PER_SAMPLE;
	else
		m_bitsPerSample = bitsPerSample;
}

Tone::~Tone()
{
}

bool Tone::writeFile(string filename, float pitch, float duration)
{
	if(pitch < 1 || pitch > 6000)
		return false;
	if(duration <= 0)
		return false;
	
	pcm_header header;
	ofstream fout(filename.c_str(), ios::out);

	int period = (int)((float)m_sampleRate/pitch);
	int sampleCount = (int)(duration * (float)m_sampleRate);
	int dataSize = sampleCount * (m_bitsPerSample/8);

	initHeader(&header);

	header.ChunkSize += uint32toLE(dataSize);
	header.SubChunk2Size = uint32toLE(dataSize);

	fout.write((char *)&header, sizeof(pcm_header));

	vector<double> wave = generateWave(period);
	
	int waveDataSize = period * (m_bitsPerSample/8);
	char *waveData = new char[waveDataSize];
	
	scaleWave(wave, waveData);
	
	int waveCount = dataSize / waveDataSize;
	
	std::cout << "Wave count=" << waveCount << std::endl;
	std::cout << "Data size=" << dataSize << std::endl;
	std::cout << "Wave data size=" << waveDataSize << std::endl;
	
	for(int i = 0;i < waveCount;i++)
		fout.write(waveData, waveDataSize);
	
	fout.write(waveData, dataSize % waveDataSize);
	
	
	delete waveData;
	
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

vector<double> Tone::generateWave(int period)
{
	vector<double> samples;
	for(int i = 0;i < period;i++) {
		samples.push_back(sin((((double)i)*TWOPI)/(double)period));
	}

	return samples;
}

// This function assumes that you have enough space in the data buffer
void Tone::scaleWave(vector<double> &wave, char *data)
{
	if(m_bitsPerSample == 16) {
		int16_t *dataPtr = (int16_t *)data;
		
		for(int i = 0; i < wave.size(); i++)
			dataPtr[i] = int16toLE((int)(wave[i] * 32767.0));
	}
	else {
		uint8_t *dataPtr = (uint8_t *)data;
		for(int i = 0;i < wave.size(); i++)
			dataPtr[i] = (uint8_t)((wave[i] + 1.0) * 255.0);
	}
}


void Tone::writeSample(int value, ofstream &out)
{
	if(m_bitsPerSample == 16) {
		int16_t sample = uint16toLE(value);
		out.write((char *)&sample, 2);
	}
	else {
		out.put(value);
	}
}

uint32_t Tone::uint32toLE(unsigned int value)
{
	return value;
}

uint16_t Tone::uint16toLE(unsigned short value)
{
	return value;
}

int16_t Tone::int16toLE(int value)
{
	return value;
}


