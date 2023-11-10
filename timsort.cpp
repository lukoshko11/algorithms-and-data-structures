#include "timsort.h"

TimSort::TimSort()
{

}


int calcMinRun(int n) {
    int r = 0;
    while (n >= MIN_MERGE) {
        r |= (n & 1); // Поддерживаем четность.
        n >>= 1;      // Делим размер массива на 2.
    }
    return n + r; // Возвращаем минимальный "run".
}

// Дополнительная функция для бинарного поиска в режиме "галопа"
int binarySearch(DynArray& arr, int start, int len, int target) {
    int lo = start;
    int hi = len;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (*arr[mid] < target) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return lo - start;
}

void merge(DynArray& arr, int left, int mid, int right) {
    int len1 = mid - left;
    int len2 = right - mid;


    auto* leftArr = new DynArray;
    leftArr->createArr(len1);
    auto* rightArr = new DynArray;
    rightArr->createArr(len2);


    for (int i = 0; i < len1; i++) {
        leftArr->array[i] = *arr[left + i];
    }
    for (int i = 0; i < len2; i++) {
        rightArr->array[i] = *arr[mid + i];
    }

    int i = 0, j = 0, k = left;
    int consecutiveCopiesL = 0, consecutiveCopiesR = 0; // Счетчик последовательных копирований
    bool galloping = false;    // Флаг режима "галопа"

    while (i < len1 && j < len2) {
        if (leftArr->array[i] <= rightArr->array[j]) {
            arr.array[k++] = leftArr->array[i++];
            consecutiveCopiesL++;
            consecutiveCopiesR = 0;
            if (consecutiveCopiesL >= 7 && !galloping) {
                // Включаем режим "галопа" и используем бинарный поиск
                int searchIdx = binarySearch(*leftArr, i, len1, rightArr->array[j]);
                int x = i;
                for (; x < searchIdx; x++) {
                    arr.array[k++] = leftArr->array[i++];
                }
                galloping = true;
                consecutiveCopiesL = 0;
            }
        }
        else {
            arr.array[k++] = rightArr->array[j++];
            consecutiveCopiesR++;
            consecutiveCopiesL = 0;
            if (consecutiveCopiesR >= 7 && !galloping) {
                // Включаем режим "галопа" и используем бинарный поиск
                int searchIdx = binarySearch(*rightArr, j, len2, leftArr->array[i]);
                int x = j;
                for (; x < searchIdx; x++) {
                    arr.array[k++] = rightArr->array[j++];
                }
                galloping = true;
                consecutiveCopiesR = 0;
            }
        }
    }

    while (i < len1) {
        arr.array[k++] = leftArr->array[i++];
    }

    while (j < len2) {
        arr.array[k++] = rightArr->array[j++];
    }
}

void insertionSort(DynArray& arr, int left, int right) {
    for (int i = left + 1; i < right; i++) {
        int key = *arr[i];
        int j = i - 1;
        while (j >= left && *arr[j] > key) {
            arr.array[j + 1] = *arr[j];
            j--;
        }
        arr.array[j + 1] = key;  // Сортировка вставкой для небольших подмассивов.
    }
}

void TimSort::sort(DynArray& arr) {
    int n = arr.getSize();
    if (n < 2)
        return;

    int minRun = calcMinRun(n); // Вычисляем минимальный размер "run" на основе размера массива.

    for (int i = 0; i < n; i += minRun) {
        int end = std::min(i + minRun, n);
        insertionSort(arr, i, end);  // Сортировка вставкой небольших подмассивов (минимальных "run").
    }

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size, n);
            int right = std::min(left + 2 * size, n);
            if (mid != right)
                merge(arr, left, mid, right);  // Объединение подмассивов с использованием Merge Sort.
        }
    }

}
