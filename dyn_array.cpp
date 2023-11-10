
#include "dyn_array.h"
#include <iostream>
#include <sstream>
#include <chrono>


DynArray::DynArray() = default;

DynArray::~DynArray() {
    delete[] array;
}

void DynArray::printArr() const {
    for (int* i = array; i != array + size; i++) {
       std::cout << *i << " ";
    }
    std::cout << "\n";
}

/// Creates dynArray with [n] numbers [value]
void DynArray::createArr(unsigned n, int value) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < n; ++i)
        array[i] = value;
}


/// Creates dynArray by array values
void DynArray::createArr(unsigned n, const int* values) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < size; ++i)
        array[i] = values[i];
}


DynArray& DynArray::operator= (const DynArray& rhs) {

    if (this == &rhs) return *this;

    delete[] array;

    size = rhs.size;
    capacity = rhs.capacity;
    array = new int[capacity];
    for (int i = 0; i < size; ++i)
        array[i-1] = rhs.array[i];

    return *this;
}


/// Print the array
std::ostream& operator<< (std::ostream& os, DynArray& arr) {
    for (int i = 0; i < arr.getSize(); ++i)
        std::cout << *arr[i] << ' ';
    return os;
}


/// Get element by it`s index via [] operator
int* DynArray::operator[] (int index) {
    return get(index);
}


/// Get element by it`s index
int* DynArray::get(int index) {
    if (isEmpty()) {
        std::cout << "IndexError: The array is empty\n";
        return nullptr;
    }
    else if (abs(index) > getSize()) {
        std::cout << "IndexError: Index out of range\n";
        return nullptr;
    }
    else if (index < 0) {
        index = int(getSize()) + index;
    }

    return &array[index];
}


/// Return index if element found else -1
int DynArray::find(int value) {
    for (int i = 0; i < getSize(); ++i)
        if (array[i] == value) return i;
    return -1;
}


///Resize the array
void DynArray::resize(unsigned newSize) {
    // No changes
    if (newSize == size)
        return;

    // New size is smaller than the current one, truncate the array
    if (newSize < size) {
        size = newSize;
        if (size < capacity / 2)
            capacity /= 2;
        return;
    }

    // New size is larger than the current capacity. Recreate the array
    if (newSize > capacity) {
        capacity *= 2;

        // Copy old values and fill empty space with default value
        int* newArray = new int[capacity];
        for (unsigned i = 0; i < size; ++i)
            newArray[i] = array[i];

        delete[] array;
        array = newArray;
    }

    // Fill new element with default value
    for (unsigned i = size; i < newSize; ++i)
        array[i] = 0;

    size = newSize;
}


/// Add element to the end
void DynArray::append(int value) {
    resize(size + 1);
    array[size - 1] = value;
}


/// Add element to the specified position
void DynArray::insert(unsigned index, int value) {
    // Index out of range
    if (index >= size) {
        std::cout << "IndexError: Index out of range\n";
        return;
    }

    // Resize and shift existing elements
    resize(size + 1);
    for (unsigned i = size - 1; i > index; --i)
        array[i] = array[i - 1];

    // Insert
    array[index] = value;
}


/// Remove element by it`s index
void DynArray::remove(unsigned index) {
    if (index >= size) {
        std::cout << "IndexError: Index out of range\n";
        return;
    }

    // Shift elements
    for (unsigned i = index; i < size - 1; ++i)
        array[i] = array[i + 1];
    resize(size - 1);
}


/// Return size of the array
unsigned DynArray::getSize() const {
    return size;
}


/// Return capacity of the array

unsigned DynArray::getCapacity() const {
    return capacity;
}


/// Return false if list is empty else true
bool DynArray::isEmpty() const {
    return size == 0;
}