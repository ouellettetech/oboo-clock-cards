#ifndef DukTapeMock_H
#define DukTapeMock_H

#include "systemFuncs.h"
#include "duktape/duk_config.h"
#include "duktape/duktape.h"

const char * DuktapeMock_get_string(duk_context *, duk_idx_t);
void DukTapeMock_Create(int size);
void DukTapeMock_Destroy(void);
const char * DukTapeMock_GetFromStack(int pos);
void DukTapeMock_PlaceOnStack(int pos, const char * val);

#endif
