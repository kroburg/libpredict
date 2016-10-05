#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifdef _WIN32
struct tm * gmtime_r(const time_t * time, struct tm *result);
struct tm * localtime_r(const time_t * time, struct tm *result);
#endif
