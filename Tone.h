#ifndef __TONE_H__
#define __TONE_H__

#include <stdint.h>
#include "wav.h"

class Tone
{
public:
  Tone(int sampleRate, int bitsPerSample);
  ~Tone();
  
  bool writeFile(string name, float pitch, float duration);
  
private:
  int m_sampleRate;
  int m_bitsPerSample;

  void initHeader(pcm_header *header);
  
  vector<int> generateWave(int period);
  
  uint32_t uint32toLE(unsigned int value);
  uint16_t uint16toLE(unsigned short value);
};

#endif
