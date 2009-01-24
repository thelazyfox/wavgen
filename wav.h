#ifndef __WAV_H__
#define __WAV_H__

#include <stdint.h>

typedef struct {
/* RIFF Header */
  uint32_t  ChunkID;
  uint32_t  ChunkSize;
  uint32_t  Format;
  
/* FMT Chunk */
  uint32_t  SubChunk1ID;
  uint32_t  SubChunk1Size;
  uint16_t  AudioFormat;
  uint16_t  NumChannels;
  uint32_t  SampleRate;
  uint32_t  ByteRate;
  uint16_t  BlockAlign;
  uint16_t  BitsPerSample;

/* DATA Chunk */
  uint32_t  SubChunk2ID;
  uint32_t  SubChunk2Size;
} __attribute__((packed)) pcm_header;

#endif
