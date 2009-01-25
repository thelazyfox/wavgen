#include <fstream>
#include "Tone.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ios;
using std::ofstream;

#define DEFAULT_SAMPLE_RATE 44100
#define DEFAULT_BITS_PER_SAMPLE 16

int main(int argc, char **argv)
{	
	vector<string> args;
	
	for(int i = 0;i < argc;i++)
		args.push_back(string(argv[i]));
		
	Tone *tone;
	
	if(args.size() == 6) {
		tone = new Tone(atoi(args[4].c_str()), atoi(args[5].c_str()));
	}
	else if(args.size() == 5) {
		tone = new Tone(atoi(args[4].c_str()));
	}
	else
		tone = new Tone();

	if(args.size() >= 4 && tone->writeFile(args[1].c_str(), atof(args[2].c_str()), atof(args[3].c_str()))) {
		cout << "Successfully created wav file" << endl;
	}
	else
		cout << "Usage: " << args[0] << " filename pitch duration <sample rate> <bits per sample>" << endl;
		
	return 0;
}
