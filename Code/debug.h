#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define Assert(cond, ...)\
  do { \
    if (!(cond)) { \
      fflush(stdout); \
      fprintf(stderr, "\33[1;31m"); \
      fprintf(stderr, __VA_ARGS__); \
      fprintf(stderr, "\33[0m\n"); \
      assert(cond); \
    } \
  } while (0);

  #define panic(format, ...) \
  Assert(0, format, ## __VA_ARGS__)

#define TODO() panic("please implement me")

#define Log_write(format, ...)

#define printflog(format, ...) \
  do { \
    printf(format, ## __VA_ARGS__); \
    fflush(stdout); \
    Log_write(format, ## __VA_ARGS__); \
  } while (0)

#define Log(format, ...) \
    printflog("\33[1;34m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

