#ifndef DIN_ARRAY_H
#define DIN_ARRAY_H
#include <iostream>

class DynArray {
private:
    int size = 0;
    unsigned capacity = 10;
    
public:
    DynArray();
    ~DynArray();
    int* array = new int[capacity];
    void createArr(unsigned size, int value = 0);
    void printArr() const;
    void createArr(unsigned, const int*);
    DynArray& operator= (const DynArray&);
    friend std::ostream& operator<< (std::ostream&, DynArray&);
    int* operator[] (int);
    int* get(int);
    int find(int);
    void resize(unsigned);
    void append(int);
    void insert(unsigned, int);
    void remove(unsigned);
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] unsigned getCapacity() const;
    [[nodiscard]] bool isEmpty() const;
};
#endif

