#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <iostream>
    #include <unistd.h>
#endif
#ifdef __linux__            // здесь модули для линуха
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <iostream>
    #include <unistd.h>
#endif
#ifdef WITH_DEBUG_UTILS
    #define debug 1
#else
    #define debug 0
#endif
#include "include/headers/debugging_utils.h"
#include "include/headers/main_framework.h"


int main() {
    ALubyte* recBuf = new ALubyte[500000];    // буфер, в который пишется запись с микро
    ALubyte* recBufptr = recBuf;         // указатель на буфер, юзаем для места, куда пишем данные
    ALint smpRec;
    record(recBufptr, &smpRec);
    ////////ДЕБАГ////////
    if (debug) {
        replay(recBuf, smpRec);
    }
    delete[] recBuf;
}
