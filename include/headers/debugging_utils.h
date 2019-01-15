#ifndef DEBUGGING_UTILS_H
#define DEBUGGING_UTILS_H

#endif // DEBUGGING_UTILS_H

#ifdef WITH_DEBUG_UTILS
    #include "../src/debug/replay.cpp"
#endif
int replay(ALbyte buffer[], ALint samples);
void determineVolume(signed char* voice_sample, int* loudest, int* quietest);

