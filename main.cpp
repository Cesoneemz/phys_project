#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <iostream>
    #include <unistd.h>
#endif
#ifdef __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
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

ALubyte recBuf[10485760];    // буфер, в который пишется запись с микро
ALubyte* recBufptr;         // указатель на буфер, юзаем для места, куда пишем данные
ALCdevice *recDev;          // устройство записи
ALint smpAvail;             // кол-во сэмплов, снятых с микро
ALint smpRec = 0;           // кол-во записанных сэмплов
ALuint rectime;             // время записи (конец записи в секундах)
const ALint REC_TIME = 5;   // время записи

int main() {
    recDev = alcCaptureOpenDevice(nullptr, 44100, AL_FORMAT_MONO16, 8000);   // получаем доступ к устройству записи
    if (recDev == nullptr) {                            // чек на ошибки
        printf("Error!! \n");
        return -1;
    }
    recBufptr = recBuf;                                 // присваиваем указателю на буфер записи адрес
                                                        // самого буфера, можно и при инициализации
    alcCaptureStart(recDev);                            // открытие устройства записи
    printf("start \n");
    rectime = time(nullptr) + REC_TIME;                 // назначение времени записи
    while (time(nullptr) < rectime) {
        alcGetIntegerv(recDev, ALC_CAPTURE_SAMPLES, 1, &smpAvail);      // получение кол-ва сэмплов для записи, запись в smpAvail
        if (smpAvail > 0) {
            alcCaptureSamples(recDev, recBufptr, smpAvail);             // запись сэмплов
            recBufptr += smpAvail * 2;                  // движение дальше по массиву, хз почему, но принтф говорит, что всё норм
            smpRec += smpAvail;                         // считаем количество сэмплов
        }
        usleep(10000);
    }
    printf("stop \n");
    alcCaptureStop(recDev);                             // кончаем запись
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    ////////ДЕБАГ////////
    if (debug) {
        replay(recBuf, smpRec);
    }
}
