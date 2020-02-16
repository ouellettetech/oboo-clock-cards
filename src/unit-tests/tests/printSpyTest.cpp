#include "CppUTest/TestHarness.h"

extern "C"
{
#include "mocks/PrintMock.h"
#include "../oboo-runtime/src/systemFuncs.h"
}

TEST_GROUP(PrintSpy)
{
    void setup()
    {
        UT_PTR_SET(print, PrintSpy);
    }

    void teardown()
    {
        PrintSpy_Destroy();
    }
};
//END: testGroup

//START: testHello
TEST(PrintSpy, HelloWorld)
{
    PrintSpy_Create(20);
    print("Hello, World\n");
    STRCMP_EQUAL("Hello, World\n", PrintSpy_GetOutput());
}
//END: testHello

//START: LimitTheOutputBufferSize
TEST(PrintSpy, LimitTheOutputBufferSize)
{
    PrintSpy_Create(4);
    print("Hello, World\n");
    STRCMP_EQUAL("Hell", PrintSpy_GetOutput());
}
//END: LimitTheOutputBufferSize

//START: PrintMultipleTimes
TEST(PrintSpy, PrintMultipleTimes)
{
    PrintSpy_Create(25);
    print("Hello");
    print(", World\n");
    STRCMP_EQUAL("Hello, World\n", PrintSpy_GetOutput());
}
//END: PrintMultipleTimes

//START: PrintMultiplePastFull
TEST(PrintSpy, PrintMultipleOutputsPastFull)
{
    PrintSpy_Create(12);
    print("12345");
    print("67890");
    print("ABCDEF");
    STRCMP_EQUAL("1234567890AB", PrintSpy_GetOutput());
}
//END: PrintMultiplePastFull
