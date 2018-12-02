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


ALubyte recBuf[1048576];    // буфер, в который пишется запись с микро
ALubyte* recBufptr;         // указатель на буфер, юзаем для места, куда пишем данные
ALCdevice *mainDev;         // устройство воспроизведения
ALCdevice *recDev;          // устройство записи
ALCcontext *ctx;            // контекст, хз что он делает, но без него не играет
ALint smpAvail;             // кол-во сэмплов, снятых с микро
ALint smpRec = 0;           // кол-во записанных сэмплов
ALuint buf;                 // буф проигрывания
ALuint src;                 // источник воспроизведения
ALuint rectime;             // время записи (конец записи в секундах)
const ALint REC_TIME = 5;   // время записи
int main() {
    recDev = alcCaptureOpenDevice(nullptr, 8000, AL_FORMAT_MONO16, 8000);   // получаем доступ к устройству записи
    if (recDev == nullptr) {                            // чек на ошибки
        std::cout << recBufptr << std::endl;
        return -1;
    }
    recBufptr = recBuf;                                 // присваиваем указателю на буфер записи адрес
                                                        // самого буфера, можно и при инициализации
    alcCaptureStart(recDev);                            // открытие устройства записи
    printf("start");
    rectime = time(nullptr) + REC_TIME;                 // назначение времени записи
    while (time(nullptr) < rectime) {
        alcGetIntegerv(recDev, ALC_CAPTURE_SAMPLES, 1, &smpAvail);      // получение кол-ва сэмплов для записи, запись в smpAvail
        if (smpAvail > 0) {
            alcCaptureSamples(recDev, recBufptr, smpAvail);             // запись сэмплов
            recBufptr += smpAvail * 2;                  // движение дальше по массиву !! не работает, хз почему
            std::cout << &recBufptr << std::endl << &recBufptr + smpAvail << std::endl; // дебаг
            smpRec += smpAvail;                         // считаем количество сэмплов
        }
    }
    printf("stop");
    alcCaptureStop(recDev);                             // кончаем запись
    alcCaptureCloseDevice(recDev);                      // отпускаем устройство
    /////////////// ДЕБАГ ПУТЁМ ВОСПРОИЗВЕДЕНИЯ ПОЛУЧЕННЫХ ДАННЫХ, ДЛЯ НАГЛЯДНОСТИ ////////////////////
    mainDev = alcOpenDevice(nullptr);                   // получаем доступ к устройству воспроизведения
    if (mainDev == nullptr) {                           // чек на ошибки
        printf("Error!! \n");
        return -1;
    }
    ctx = alcCreateContext(mainDev, nullptr);           // создание контекста, хз чо эт, но openal хочет
    if (ctx == nullptr) {
        std::cout << recBufptr << std::endl;
        return -1;
    }
    alcMakeContextCurrent(ctx);                         // выбор контекста
    alGenBuffers(1, &buf);                              // делаем буфер воспроизведения
    alBufferData(buf, AL_FORMAT_MONO16, recBuf, smpRec, 8000);  // загружаем в него данные из буфера записи
    alGenSources(1, &src);                              // создаём источник звука
    alSourcei(src, AL_BUFFER, buf);                     // связываем его с буфером
    alSourcePlay(src);                                  // проигрываем содержимое буфера
    usleep(5000000);                                    // ждём конца проигрывания
    alcCloseDevice(mainDev);                            // отпускаем устройство воспроизведения
    // тут нужно ещё почистить следы, поудалять буферы, отправить ссылки в ноль
    /////////////// КОНЕЦ ДЕБАГА ////////////////////////////
}
