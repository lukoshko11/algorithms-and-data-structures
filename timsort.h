//#pragma once
#ifndef TIMSORT_H
#define TIMSORT_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include "dyn_array.h"
#include "quicksort.h"

const int MIN_MERGE = 64;  // Минимальный размер "run", используемый в Timsort.

class TimSort {
public:
    static void sort(DynArray& arr);
    TimSort();
};

#endif // TIMSORT_H