#include "PrintMock.h"
#include "CppUTest/TestHarness_c.h"
#include <stdio.h>
#include <stdarg.h>
#define WINDOWS_VSNPRINTF_OVERWRITE -1
#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

#include <stdlib.h>
static char * mBuffer = 0;
static long mSize = 0;
static int mOffset = 0;
static int mUsed = 0;

void PrintMock_Create(int size){
    PrintMock_Destroy();
    mSize = size+1;
    mBuffer = (char *)calloc(mSize, sizeof(char));
    mOffset = 0;
    mUsed = 0;
    mBuffer[0] = '\0';
}

int PrintMock(const char * format, ...){
    long wSize;
    va_list args;
    va_start(args, format);
    wSize = vsnprintf(mBuffer + mOffset, mSize - mUsed, format, args);

    if(wSize == WINDOWS_VSNPRINTF_OVERWRITE){
        wSize = mSize - mUsed;
        mBuffer[mOffset + wSize- 1] = 0;
    }

    mOffset += wSize;
    mUsed += wSize;
    va_end(args);
    return 1;
}

void PrintMock_Destroy(void){
    if (mBuffer == 0){
        return;
    }

    free(mBuffer);
    mBuffer = 0;
}

const char * PrintMock_GetOutput(void){
    return mBuffer;
}