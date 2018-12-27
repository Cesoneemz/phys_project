#ifndef MAIN_FRAMEWORK_H
#define MAIN_FRAMEWORK_H

#endif // MAIN_FRAMEWORK_H

int record(ALint *recBufptr, ALint *smpRecReturn, ALint rec_time);    // *recbufptr - указатель на массив, в который писать, *smpRecReturn - тут переменная, в которую пишется количество сэмплов
// e.g. record(recBufptr, &smpRec);
char recognise(signed int* voice, int* smpRec);
