#include "application.h"
#include <iostream>
#include "dyn_array.h"
#include "quicksort.h"
#include "timsort.h"

using namespace std;

int checking() {
    int a;
    while (true)
    {
        cin >> a;
        if (std::cin.fail())
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        break;
    }
    return a;
}
char checking1() {
    char a;
    while (true)
    {
        cin >> a;
        if (std::cin.fail())
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        break;
    }
    return a;
}
Application::Application()
= default;

void Application::exec() {
    char input;
    int t;
    do {
        t = 0;
        cout << "Menu:\n1 - Timsort\n2 - Quicksort\n0 - Exit\n";
        input = checking1();
        if (input == '0') break;
        string str;
        auto* arr = new DynArray;
        cout << "Size: ";
        int size;
        size = checking();
        if (input == '1') {
            int* values = new int[size]();
            cout << "Enter " << size << " elements separated by space:\n";
            for (int i = 0; i < size; i++)
                if (!(cin >> values[i])) {
                    cout << "Invalid input";
                    break;
                }
            // Reassign the array
            arr->createArr(size, values);
            cout << "Created array: ";
            arr->printArr();
            cout << "After Timsort: ";
            TimSort::sort(*arr);
            arr->printArr();
        }
        else if (input == '2') {
            int* values = new int[size]();
            cout << "Enter " << size << " elements separated by space:\n";
            for (int i = 0; i < size; i++)
                if (!(cin >> values[i])) {
                    cout << "Invalid input";
                    break;
                }
            // Reassign the array
            arr->createArr(size, values);
            cout << "Created array: ";
            arr->printArr();
            cout << "After quicksort: ";
            QuickSort::quickSort(arr->array, 0, arr->getSize() - 1);
            arr->printArr();
        }
        delete arr;
        cout << "Do you want to continue? yes - 1; no - 0\n";
        cin >> t;
        system("cls");
    } while (t != 0);
}