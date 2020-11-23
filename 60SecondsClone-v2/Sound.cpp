#include "Sound.h"

void playMusic(const char* fileName) {
	PlaySound(TEXT(fileName), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC | SND_NODEFAULT);
}

void stopMusic() {
	PlaySound(NULL, 0, 0);
}
