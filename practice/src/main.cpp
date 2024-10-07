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
class foo
{
  public:
    foo() { std::cout << "ctor" << std::endl; }
    foo(const foo &) { std::cout << "copy ctor" << std::endl; }
};

foo createFoo_1()
{
    foo object;  // "ctor"
    return object;
}

foo createFoo_2()
{
    return foo(); // "ctor"
}

int main()
{
    foo obj = createFoo_1();  // "copy ctor"
    foo obj = createFoo_2();  // no "copy ctor" print
}