#ifndef __Helpers_H__
#define __Helpers_H__

void OutputMessage(const char* message, ...);
char* LoadCompleteFile(const char* filename, long* length);
double GetSystemTime();
double GetSystemTimeSinceGameStart();

#endif //__Helpers_H__
