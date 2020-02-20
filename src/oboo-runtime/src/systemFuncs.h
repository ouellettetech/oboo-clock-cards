/***
 * File to contain system overloads so that we can unit test them.
 * 
 * 
***/
#include "duktape/duk_config.h"
#ifndef SYSTEM_FUNC_H
#define SYSTEM_FUNC_H
#if 0
int print(const char *, ...);
const char * duc_get_string(duk_context *, duk_idx_t);
#endif 

extern int (*print)(const char *, ...);

extern const char * (*js_get_string)(duk_context *, duk_idx_t);

extern void mysleep(int seconds);

#endif  /* SYSTEM_FUNC_H */
