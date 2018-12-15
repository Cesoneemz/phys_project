#ifdef _WIN32
	#include <al.h>
	#include <alc.h>
	#include <cstdio>
	#include <chrono>
	#include <thread>
#elif __linux__
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <cstdio>
    #include <chrono>
    #include <thread>
#endif

int replay(ALbyte buffer[], ALint samples) {
	ALCdevice *mainDev;         // устройство воспроизведения
	ALCcontext *ctx;            // контекст, хз что он делает, но без него не играет
	ALuint buf;                 // буф проигрывания
	ALuint src;                 // источник воспроизведения
    ALbyte* bufptr = buffer;
	mainDev = alcOpenDevice(nullptr);                   // получаем доступ к устройству воспроизведения
    if (mainDev == nullptr) {                           // чек на ошибки
        printf("Error!! \n");
        return -1;
    }
    ctx = alcCreateContext(mainDev, nullptr);           // создание контекста, хз чо эт, но openal хочет
    if (ctx == nullptr) {
        printf("Error!\n");
        return -1;
    }
    alcMakeContextCurrent(ctx);                         // выбор контекста
    alGenBuffers(1, &buf);                              // делаем буфер воспроизведения
    alBufferData(buf, AL_FORMAT_MONO16, bufptr, samples*2, 44100);  // загружаем в него данные из буфера записи
    alGenSources(1, &src);                              // создаём источник звука
    alSourcei(src, AL_BUFFER, buf);                     // связываем его с буфером
    alSourcePlay(src);                                  // проигрываем содержимое буфера
	std::this_thread::sleep_for(std::chrono::seconds(5));// ждём конца проигрывания
    alcCloseDevice(mainDev);                            // отпускаем устройство воспроизведения
    // тут нужно ещё почистить следы, поудалять буферы, отправить ссылки в ноль
    return 1;
}
