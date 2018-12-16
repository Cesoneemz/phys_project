#include <fstream>

#define SAMPLE_DIRECTORY "include/src/samples/"     // СДЕЛАТЬ ОТНОСИТЕЛЬНЫЙ ПУТЬ К ФАЙЛУ
#define SAMPLE_A SAMPLE_DIRECTORY"A.raw"

void loadSample(const char* filename, long *length);
void determineVolume(unsigned char* voice_sample, int* loudest, int* quietest);

static std::ifstream read;
static long length;
static int* sample;

char recognise(signed char* voice) {
    int* sample;
    loadSample(SAMPLE_A, &length);          // СДЕЛАТЬ РАСПОЗНАВАНИЕ


    return 'a';
}
void loadSample(const char* filename, long *length) {
    read.open(filename, std::ifstream::binary);
    if (!read.is_open())
        printf("Ne rabotaet\n");
    int file_length = 840;
    char* sample_internal = new char[file_length];
    read.read(sample_internal, file_length);
    sample = new int[file_length/2];
    int* sampleptr = sample;
    for (int i = 0; i < file_length; i+=2) {
        *sampleptr = reinterpret_cast<int>(sample_internal[i]+sample_internal[i+1]);
        sampleptr++;
    }
}
