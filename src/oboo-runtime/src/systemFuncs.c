/***
 * File to contain system overloads so that we can unit test them.
 * 
 * 
***/
#include "systemFuncs.h"
#include <stdio.h>

int (*print)(const char * format, ...) = printf;
