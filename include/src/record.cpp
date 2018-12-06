#ifdef _WIN32               // здесь модули для винды, если что-то будет требовать, закидываешь сюда
    #include <al.h>
    #include <alc.h>
    #include <time.h>
    #include <unistd.h>
    #include <cstdio>
#endif
#ifdef __linux__            // здесь модули для линуха
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <time.h>
    #include <unistd.h>
    #include <cstdio>
#endif
int record(ALubyte *recBufptr, ALint *smpRecReturn) {                       // у функции на входе указатель на массив
    ALCdevice *recDev;          // устройство записи                        // также выводится количество сэмплов
    ALint smpAvail;             // кол-во сэмплов, снятых с микро
    ALint smpRec = 0;           // кол-во записанных сэмплов
    ALuint rectime;             // время записи (конец записи в секундах)
    const ALint REC_TIME = 5;   // время записи
    recDev = alcCaptureOpenDevice(nullptr, 44100, AL_FORMAT_MONO16, 8000);   // получаем доступ к устройству записи
    if (recDev == nullptr) {                            // чек на ошибки
        printf("Error with opening capture device!! \n");
        return -1;
    }
    alcCaptureStart(recDev);                            // открытие устройства записи
    printf("Started recording!\n");
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
    printf("Stopped recording!\n");
    alcCaptureStop(recDev);                             // кончаем запись
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    *smpRecReturn = smpRec;
    return 1;
}
