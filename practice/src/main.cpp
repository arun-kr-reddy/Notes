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

#include <tuple>

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
int main()
{
    int first = 1, second = 2, third = 3;

    std::tuple<int, int, int> tp = std::tie(first, second, third);

    std::tie(first, second, third) = tp;

    // alternate
    // first  = std::get<0>(tp);
    // second = std::get<1>(tp);
    // third  = std::get<2>(tp);

    return 0;
}

int binary_search(int arr[], int low, int high, int x)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binary_search(arr, low, mid - 1, x);

        return binary_search(arr, mid + 1, high, x);
    }

    return -1;
}