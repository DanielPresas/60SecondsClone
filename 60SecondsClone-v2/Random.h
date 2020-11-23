#pragma once

#include <random>
#include <ctime>
#include <chrono>

typedef std::chrono::system_clock sysClock;

int randomInt(int low, int high);
bool randomBool();