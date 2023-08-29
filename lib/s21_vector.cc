#include "s21_vector.h"

#include <iostream.h>

template<class T> // , class Allocator = std::allocator<T>
class Vector {
    T* data;
    size_t size;
    size_t capacity;
};