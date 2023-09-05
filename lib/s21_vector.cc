#include "s21_vector.h"

template<class T> size_t Vector<T>::size() const noexcept {
    return v_size;
}

template<class T> size_t Vector<T>::capacity() const noexcept {
    return v_capacity;
}

template<class T> void Vector<T>::reserve(size_t n) {
    if (n <= v_capacity) return;
    T* new_data = reinterpret_cast<T*>(new char[n * sizeof(T)]);
    try {
        std::uninitialized_copy(data, data + v_size, new_data);
    } catch (...) {
        delete[] reinterpret_cast<char*>(new_data);
        throw;
    }
    for (size_t i = 0; i < v_size; ++i) {
        data[i].~T();
    }
    delete[] reinterpret_cast<char*>(data);
    new_data = data;
    v_capacity = n;
}

template<class T> void Vector<T>::resize(size_t n, const T& value = T()) {
    if (n > v_capacity) reserve(n);
    size_t i = v_size
    try {
        for (; i < n; ++i) {
            new (data + i) T(value);
        }
    } catch (...) {
        for (size_t j = v_size; j < i, ++j) {
            data[i].~T();
        }
        delete[] reinterpret_cast<char*>(new_data);
        throw;
    }    
    if (n < v_size) {
        v_size = n;
    }
}

template<class T> void Vector<T>::push_back(const T& value) {
    if (v_capacity == v_size) {
        reserve(2 * v_size);
    }
    new (data + v_size) T(value);  // TODO: try catch
    ++v_size;
}

template<class T> void Vector<T>::pop_back() {
    --v_size;
}