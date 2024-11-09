#ifndef log_h
#define log_h

void logInit();
void consoleLog(const char *text1, float value1, int interval = 500);
void consoleLog(const char *text1, float value1, const char *text2, float value2, int interval = 500);
void consoleLog(const char *text1, float value1, const char *text2, float value2,const char *text3, float value3, int interval = 500);
void consoleLog(const char *text1, float value1, const char *text2, float value2, const char *text3, float value3, const char *text4, float value4,  int interval = 500);

#endif