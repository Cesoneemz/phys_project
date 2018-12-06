#include <AL/al.h>
#include <AL/alc.h>
#include <cstdio>
#include <unistd.h>

//int main() {
//    printf("lal");
//}

int replay(ALubyte buffer[], ALuint samples) {
	ALCdevice *mainDev;         // устройство воспроизведения
	ALCcontext *ctx;            // контекст, хз что он делает, но без него не играет
	ALuint buf;                 // буф проигрывания
	ALuint src;                 // источник воспроизведения
    ALubyte* bufptr = buffer;
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
    alBufferData(buf, AL_FORMAT_MONO16, bufptr, samples, 8000);  // загружаем в него данные из буфера записи
    alGenSources(1, &src);                              // создаём источник звука
    alSourcei(src, AL_BUFFER, buf);                     // связываем его с буфером
    alSourcePlay(src);                                  // проигрываем содержимое буфера
    usleep(5000000);                                    // ждём конца проигрывания
    alcCloseDevice(mainDev);                            // отпускаем устройство воспроизведения
    // тут нужно ещё почистить следы, поудалять буферы, отправить ссылки в ноль
    return 1;
}
