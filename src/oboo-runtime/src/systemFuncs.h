/***
 * File to contain system overloads so that we can unit test them.
 * 
 * 
***/

#ifndef SYSTEM_FUNC_H
#define SYSTEM_FUNC_H
#if 0
int print(const char *, ...);
#endif 

extern int (*print)(const char *, ...);

#endif  /* SYSTEM_FUNC_H */