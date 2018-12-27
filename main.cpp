#ifdef _WIN32	           // здесь модули для винды, если что-то будет требовать, закидываешь сюда
	#include <al.h>
	#include <alc.h>
	#include <chrono>
	#include <thread>
#elif __linux__	        // здесь модули для линуха
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <chrono>
	#include <thread>
	#include <cstring>
#endif
#ifdef WITH_DEBUG_UTILS
	#define debug 1
#else
	#define debug 0
#endif
#include "include/headers/debugging_utils.h"
#include "include/headers/main_framework.h"
#define REC_TIME 5


int main() {
	ALbyte* recBuf = new ALbyte[500000];    // буфер, в который пишется запись с микро
	ALint smpRec = 0;
						// TODO: сделать циклический буфер с оффсетом в n байтов
	std::thread recording(record, reinterpret_cast<ALint*>(recBuf), &smpRec, REC_TIME);	// готово
	std::thread recognition(recognise, reinterpret_cast<int*>(recBuf), &smpRec);		// TODO
	

	////////ДЕБАГ////////
	if (debug) {
		replay(recBuf, smpRec);
	}

	recognition.join();
	recording.join();

	delete[] recBuf;
}
