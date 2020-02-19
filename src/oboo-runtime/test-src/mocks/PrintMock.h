#ifndef PrintMock_H
#define PrintMock_H

#include "systemFuncs.h"

int PrintMock(const char * format, ...);
void PrintMock_Create(int size);
void PrintMock_Destroy(void);
const char * PrintMock_GetOutput(void);

#endif
