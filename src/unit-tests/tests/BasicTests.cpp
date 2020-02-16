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
	/*
	 * Add your c-only include files here
	 */
}
/**
 * @brief Basic Tests for those that I don't have a better category for.
 * 
 */
TEST_GROUP(BasicTests)
{
    void setup()
    {
//        UT_PTR_SET(print, PrintSpy);
    }

    void teardown()
    {
//        PrintSpy_Destroy();
    }
};

/**
 * @brief Test Should check that Print Function calls the native C Print Function
 * and appends \n to the string.
 * 
 */
TEST(BasicTests, NativePrint)
{
    //PrintSpy_Create(20);
    //native_print(NULL);
    //char *initString = (char*) duk_to_string(ctx, 0);
    //STRCMP_EQUAL("Hello, World\n", PrintSpy_GetOutput()); 
    /*
     * Instantiate your class, or call the function, you want to test.
     * Then delete this comment
     */
}


