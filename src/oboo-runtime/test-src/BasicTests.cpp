/**
 * @file BasicTests.cpp
 * @author Bradley Ouellette (bradou@ouellettetech.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "CppUTest/TestHarness.h"
//#include "src/runtime.h"

extern "C"
{
#include "mocks/PrintMock.h"
#include "mocks/DuktapeMock.h"
#include "systemFuncs.h"
#include "runtime.h"
}

/**
 * @brief Basic Tests for those that I don't have a better category for.
 * 
 */
TEST_GROUP(BasicTests)
{
    void setup()
    {
        UT_PTR_SET(print, PrintMock);
        UT_PTR_SET(js_get_string, DuktapeMock_get_string);
    }

    void teardown()
    {
        PrintMock_Destroy();
        DukTapeMock_Destroy();
    }
};

/**
 * @brief Test Should check that Print Function calls the native C Print Function
 * and appends \n to the string.
 * 
 */
TEST(BasicTests, NativePrint)
{
    PrintMock_Create(20);
    DukTapeMock_Create(5);
    DukTapeMock_PlaceOnStack(0,"Hello, World");
    native_print(nullptr);
    STRCMP_EQUAL("Hello, World\n", PrintMock_GetOutput()); 
}


