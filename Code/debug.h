#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// #define L3DEBUG
#define L4DEBUG

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

#define LogRed(format, ...) \
    printflog("\33[1;31m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LogGreen(format, ...) \
    printflog("\33[1;32m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LogYellow(format, ...) \
    printflog("\33[1;33m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LogPurple(format, ...) \
    printflog("\33[1;35m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define LogWhite(format, ...) \
    printflog("\33[1;37m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

        