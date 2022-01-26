#include "Utils.h"

#ifdef _WIN32

void sleep(DWORD dwMilliseconds)
{
	Sleep(dwMilliseconds * 1000);
}
void usleep(DWORD dwMilliseconds)
{
	Sleep(dwMilliseconds);
}

#endif

bool strtoi(char* value, int* result)
{
	char* p;
	errno = 0;
	long arg = strtol(value, &p, 10);
	if (*p != '\0' || errno != 0) {
		return false;
	}
	if (arg < INT_MIN || arg > INT_MAX) {
		return false;
	}
	*result = arg;
	return true;
}