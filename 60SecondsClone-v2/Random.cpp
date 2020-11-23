#include "Random.h"

std::default_random_engine generator;

int randomInt(int low, int high) {
	sysClock::time_point epoch = sysClock::from_time_t(time(nullptr));
	sysClock::time_point check = sysClock::now();

	sysClock::duration duration = epoch - check;

	generator.seed(duration.count());
	std::uniform_int_distribution<> integers(low, high);

	int randomInt = integers(generator);
	return randomInt;
}

bool randomBool() {
	int result = randomInt(0, 1);

	if (result == 0) return false;
	else return true;
}
