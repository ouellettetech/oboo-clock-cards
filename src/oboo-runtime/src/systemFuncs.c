/***
 * File to contain system overloads so that we can unit test them.
 * 
 * 
***/
#include "systemFuncs.h"
#include <stdio.h>
#include "duktape/duk_config.h"
#include "duktape/duktape.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int (*print)(const char * format, ...) = printf;
const char * (*js_get_string)(duk_context * ctx, duk_idx_t idx) = duk_to_string;

void mysleep(int seconds){
  //sleep:
  #ifdef _WIN32
  Sleep(seconds);
  #else
  usleep(seconds*1000);  /* sleep for 100 milliSeconds */
  #endif
}