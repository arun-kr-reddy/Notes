﻿// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// ************************************************************************************************************************************************************
// types
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// declarations
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
int foo(int arg)
{
    printf("foo %d\n", arg);
    return arg;
}

int main()
{
    short a = 1024;
    int b   = 5;
    b       = a;                  // implicit conversion
    std::cout << b << std::endl;  // "5"

    float c    = 10.5;
    uint32_t d = c;               // decimal dropped
    std::cout << d << std::endl;  // "10"

    return 0;
}