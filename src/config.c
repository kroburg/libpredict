#include <time.h>

#include "config.h"

#ifdef _WIN32
struct tm * gmtime_r(const time_t * time, struct tm *result)
{
  gmtime_s(result, time);
  return result;
}

struct tm * localtime_r(const time_t * time, struct tm *result)
{
  localtime_s(result, time);
  return result;
}
#endif