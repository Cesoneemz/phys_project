#ifndef DEBUGGING_UTILS_H
#define DEBUGGING_UTILS_H

#endif // DEBUGGING_UTILS_H
#include <AL/al.h>
#ifdef WITH_DEBUG_UTILS
    #include "../src/debug/replay.cpp"
#endif
int replay(ALubyte buffer[], ALuint samples);
