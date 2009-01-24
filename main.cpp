#include <fstream>

void write_tone(string filename, float frequency, float duration, int sampleRate);

int main()
{

}

void write_tone(string filename, float frequency, float duration, int sampleRate)
{
  int sampleCount = (int)(duration * (float)sampleRate);
  
  ofstream fout(filename, ios::out);
  
  // Wav files always start with this
  fout << 0x56 << 0x49 << 0x46 << 0x46;
  
}
