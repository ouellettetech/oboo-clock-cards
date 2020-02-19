#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char** av)
{
    printf("tests running...");
    return CommandLineTestRunner::RunAllTests(ac, av);
}

