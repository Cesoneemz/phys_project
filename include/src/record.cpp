#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <Synchapi.h>
    #include <cstdio>
#endif
#ifdef __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <time.h>
    #include <unistd.h>
    #include <cstdio>
#endif

void sleep(unsigned int time) {
#ifdef _WIN32
	Sleep(time);
#endif
#ifdef __linux__
	usleep(time * 1000);
#endif
}

int record(ALubyte *recBufptr, ALint *smpRecReturn) {                       // у функции на входе указатель на массив
    ALCdevice *recDev;          // устройство записи                        // также выводится количество сэмплов
    ALint smpAvail;             // кол-во сэмплов, снятых с микро
    ALint smpRec = 0;           // кол-во записанных сэмплов
    const ALint REC_TIME = 5;   // время записи
    recDev = alcCaptureOpenDevice(nullptr, 44100, AL_FORMAT_MONO16, 44100*REC_TIME);   // получаем доступ к устройству записи
    if (recDev == nullptr) {                            // чек на ошибки
        printf("Error with opening capture device!! \n");
        return -1;
    }
    alcCaptureStart(recDev);                            // открытие устройства записи
    printf("Started recording!\n");
    sleep(REC_TIME*1000);
    alcGetIntegerv(recDev, ALC_CAPTURE_SAMPLES, 1, &smpAvail);
    alcCaptureSamples(recDev, recBufptr, smpAvail);
    smpRec=smpAvail;
    printf("Stopped recording!\n");
    alcCaptureStop(recDev);                             // кончаем запись
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    *smpRecReturn = smpRec;
    return 1;
}
