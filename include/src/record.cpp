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

int record(ALint *recBufptr, ALint *smpRecReturn, ALint rec_time) {                       // у функции на входе указатель на массив
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
    printf("Stopped recording!\n");
    alcCaptureStop(recDev);                             // кончаем запись
    // while(!is_buffer1_available && !is_buffer2_available)
    //     std::this_thread::yield();
    // if (is_buffer1_available)
    //     alcCaptureSamples(recDev, recBuf1ptr, smpAvail);
    // else
    //     alcCaptureSamples(recDev, recBuf2ptr, smpAvail);
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    *smpRecReturn = smpAvail;
    return 0;
}
