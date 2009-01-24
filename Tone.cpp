#include "Tone.h"

#include <math.h>

#define PI 3.14159265

Tone::Tone(int sampleRate)
{
}

Tone::~Tone()
{
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

uint32_t Tone::uint32toLE(unsigned int value)
{
  return value;
}

uint16_t Tone::uint16toLE(unsigned short value)
{
  return value;
}

vector<int> Tone::generateWave(int period)
{
  double twopi = pi * 2.0;
  double increment = twopi/((float)period);
  
  for(int i = 0;i < period;i++)
}

