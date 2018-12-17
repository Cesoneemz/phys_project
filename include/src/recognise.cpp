#include <fstream>
#include <cstring>
#include "../headers/samples.h"

void loadSample(const char* filename, long *length);
void determineVolume(signed char* voice_sample, int* loudest, int* quietest);

static std::ifstream read;
static long length;
static short int** samples = new short int*[SAMPLES_COUNT];
*samples[0] = new short int[SAMPLE_A_LENGTH/2];

char recognise(signed char* voice, int* smpRec) {
	int* sample;
	loadSample(SAMPLE_A, &length);          // СДЕЛАТЬ РАСПОЗНАВАНИЕ


	return 'a';
}
int loadSamples() {
	
	char* filenames[SAMPLES_COUNT] { SAMPLE_A };
	int filesizes[SAMPLES_COUNT] { SAMPLE_A_LENGTH };
	char* internal_sample;
	for (int i = 0; i < SAMPLES_COUNT; i++) {
	    read.open(filenames[i], std::ifstream::binary);
		if (!read.is_open()) {
	        	printf("Error opening file %s\n", filenames[i]);
			return -1;
		}
		internal_sample = new char[filesizes[i]];
		read.read(internal_sample, filesizes[i]);
		short int* samplePtr = samples[i];
		char* pcm = "";
		for (int k = 0; k < filesizes[i]; k+=2) {
			strcpy(pcm, internal_sample[k]);
			strcpy(pcm, internal_sample[k+1]);
			*samplePtr = reinterpret_cast<short int>(pcm);
			samplePtr += sizeof(short int);
			pcm = "";
		}
	}
}
