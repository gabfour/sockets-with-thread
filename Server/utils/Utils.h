#ifndef UTILS_H_
#define UTILS_H_

#include "CrossPlatform.h"

#ifdef _WIN32

void sleep(DWORD dwMilliseconds);
void usleep(DWORD dwMilliseconds);

#endif

bool strtoi(char* value, int* result);

#endif