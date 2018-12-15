#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <iostream>
    #include <chrono>
    #include <thread>
#elif __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <chrono>
    #include <thread>
    #include <iostream>
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
    ALbyte* recBuf = new ALbyte[500000];    // буфер, в который пишется запись с микро
    ALbyte* recBufptr = recBuf;         // указатель на буфер, юзаем для места, куда пишем данные
    ALint smpRec;
    //record(recBufptr, &smpRec, REC_TIME);
    ////////ДЕБАГ////////
    if (debug) {
        //replay(recBuf, smpRec);
    }
    recognise(recBuf);
    delete[] recBuf;
}
