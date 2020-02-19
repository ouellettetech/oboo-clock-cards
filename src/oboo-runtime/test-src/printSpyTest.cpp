#include "CppUTest/TestHarness.h"

extern "C"
{
#include "mocks/PrintMock.h"
#include "systemFuncs.h"
}

TEST_GROUP(PrintSpy)
{
    void setup()
    {
        UT_PTR_SET(print, PrintMock);
    }

    void teardown()
    {
        PrintMock_Destroy();
    }
};
//END: testGroup

//START: testHello
TEST(PrintSpy, HelloWorld)
{
    PrintMock_Create(20);
    print("Hello, World\n");
    STRCMP_EQUAL("Hello, World\n", PrintMock_GetOutput());
}
//END: testHello

//START: LimitTheOutputBufferSize
TEST(PrintSpy, LimitTheOutputBufferSize)
{
    PrintMock_Create(4);
    print("Hello, World\n");
    STRCMP_EQUAL("Hell", PrintMock_GetOutput());
}
//END: LimitTheOutputBufferSize

//START: PrintMultipleTimes
TEST(PrintSpy, PrintMultipleTimes)
{
    PrintMock_Create(25);
    print("Hello");
    print(", World\n");
    STRCMP_EQUAL("Hello, World\n", PrintMock_GetOutput());
}
//END: PrintMultipleTimes

//START: PrintMultiplePastFull
TEST(PrintSpy, PrintMultipleOutputsPastFull)
{
    PrintMock_Create(12);
    print("12345");
    print("67890");
    print("ABCDEF");
    STRCMP_EQUAL("1234567890AB", PrintMock_GetOutput());
}
//END: PrintMultiplePastFull
