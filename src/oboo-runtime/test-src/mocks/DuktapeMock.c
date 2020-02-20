#include "DuktapeMock.h"
#include "CppUTest/TestHarness_c.h"
#include <stdio.h>
#include <stdarg.h>
#define WINDOWS_VSNPRINTF_OVERWRITE -1
#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

#include <stdlib.h>
static char** variables = 0;
static duk_context *context = NULL;
static int mSize;

const char* DuktapeMock_get_string(duk_context *ctx, duk_idx_t index){
    context = ctx;
    if (index < mSize){
        return variables[index];
    } else {
        return "Invalid index";
    }
}

void DukTapeMock_Create(int size){
    DukTapeMock_Destroy();
    mSize = size;
    variables = (char **)calloc(mSize, sizeof(char *));
    for(int i=0;i<size;i++){
        variables[i]=0;
    }
}

void DukTapeMock_Destroy(void){
    if (variables == 0){
        return;
    }
    for(int i=0;i<mSize;i++){
        if(variables[i]!=0){
            free(variables[i]);
        }
    }
    free(variables);
    variables = 0;
}

const char * DukTapeMock_GetFromStack(int pos){
    return variables[pos];
}

void DukTapeMock_PlaceOnStack(int pos, const char * val){
    int newStringLen = strlen(val);
    char * mBuffer;
    mBuffer = (char *)calloc(newStringLen, sizeof(char)+1);
    strcpy(mBuffer,val);
    variables[pos] = mBuffer;
}