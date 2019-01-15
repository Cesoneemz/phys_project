#include "../headers/samples.h"

void normalizeVolume(int16_t* voice_sample, unsigned int sample_count) {
	*loudest = 0;
	for (int i = 0; i < samples_count; i++) {
		if (abs(*(voice_sample + i)) > abs(*loudest))
			*loudest = *(voice_sample + i);
	}
	unsigned double coeff = abs(32768 / *loudest);
	for (int i = 0; i < samples_count; i++)
		*(voice_sample + i) *= coeff;
}

static long length;

char recognise(int16_t* voice_sample, unsigned int* smpRec) {
    int16_t sample = *voice_sample;
    unsigned int sample_lenght = *smpRec;
        //printf("%p\n", samples[0]);
        //loadSamples(SAMPLE_A, &length);          // СДЕЛАТЬ РАСПОЗНАВАНИЕ


	return 'a';
}

