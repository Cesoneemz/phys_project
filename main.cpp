#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <chrono>
    #include <thread>
#elif __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <chrono>
    #include <thread>
#endif
#ifdef WITH_DEBUG_UTILS
    #define debug 1
#else
    #define debug 0
#endif
#include "include/headers/debugging_utils.h"
#include "include/headers/main_framework.h"
#define REC_TIME 5


int main() {
    ALbyte** recBuf = new ALbyte*[2];
    recBuf[0] = new ALbyte[500000];    // буфер, в который пишется запись с микро
    recBuf[1] = new ALbyte[500000];
    ALint smpRec;
    //printf("%p\n%p\n", recBuf[0], recBuf[1]);
    std::thread recording(record, recBuf[0], recBuf[1], &smpRec, REC_TIME);
    std::thread recognition(recognise, recBuf[0]);
    ////////ДЕБАГ////////
    /*if (debug) {
        replay(recBufptr, smpRec[0]);
    }*/
    recognition.join();
    recording.join();
    delete[] recBuf[0], recBuf[1], recBuf;
}
