#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <chrono>
	#include <thread>
    #include <cstdio>
#endif
#ifdef __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <chrono>
    #include <thread>
    #include <cstdio>
#endif


int record(ALbyte *recBufptr, ALint *smpRecReturn, ALint rec_time) {                       // у функции на входе указатель на массив
    ALCdevice *recDev;          // устройство записи                        // также выводится количество сэмплов
    ALint smpAvail;             // кол-во сэмплов, снятых с микро
    //const ALint REC_TIME = 5;   // время записи
    recDev = alcCaptureOpenDevice(nullptr, 44100, AL_FORMAT_MONO16, 44100*rec_time);   // получаем доступ к устройству записи
    if (recDev == nullptr) {                            // чек на ошибки
        printf("Error with opening capture device!! \n");
        return -1;
    }
    alcCaptureStart(recDev);                            // открытие устройства записи
    printf("Started recording!\n");
    std::this_thread::sleep_for(std::chrono::seconds(rec_time));
    alcGetIntegerv(recDev, ALC_CAPTURE_SAMPLES, 1, &smpAvail);
    alcCaptureSamples(recDev, recBufptr, smpAvail);
    printf("Stopped recording!\n");
    alcCaptureStop(recDev);                             // кончаем запись
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    *smpRecReturn = smpAvail;
    return 1;
}
