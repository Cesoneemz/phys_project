#include <fstream>
#include "../headers/samples.h"

void loadSample(const char* filename, long *length);
void determineVolume(signed char* voice_sample, int* loudest, int* quietest);

static std::ifstream read;
static long length;
static short int** samples = new short int*[SAMPLES_COUNT];
samples[0] = new short int[SAMPLE_A_LENGTH/2];

char recognise(signed char* voice, int* smpRec) {
	int* sample;
	loadSample(SAMPLE_A, &length);          // СДЕЛАТЬ РАСПОЗНАВАНИЕ


	return 'a';
}
void loadSamples() {
	
	char* filenames[SAMPLES_COUNT] { SAMPLE_A };
	int filesizes[SAMPLES_COUNT] { SAMPLE_A_LENGTH };
	char* internal_sample;
	for (int i = 0; i < SAMPLES_COUNT; i++) {
	    read.open(filenames[i], std::ifstream::binary);
		if (!read.is_open()) {
	        	printf("Error opening file %s\n", filenames[i];
			return -1;
		}
		internal_sample = new char[filesizes[i]];
		read.read(internal_sample, filesizes[i]);
		short int* samplePtr = samples[i];
		for (int k = 0; k < filesizes[i]; k+=2) {
			*samplePtr = reinterpret_cast<short int>(internal_sample[k] + internal_sample[k+1]);
			samplePtr += sizeof(short int);
		}
	}
}
