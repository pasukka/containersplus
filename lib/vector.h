#ifndef CONTAINERS_LIB_VECTOR_H_
#define CONTAINERS_LIB_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class vector {
  using alloc_traits = std::allocator_traits<Allocator>;
  using reference = T&;
  using const_reference = const T&;
  using value_type = T;

  typedef typename alloc_traits::value_type allocator_type;
  typedef typename alloc_traits::size_type size_type;
  // typedef typename alloc_traits::pointer pointer;
  // typedef typename alloc_traits::const_pointer const_pointer;

  T* v_data;
  size_type v_size;
  size_type v_capacity;
  Allocator v_alloc;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  vector() noexcept(noexcept(Allocator()))
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()){};

  vector(size_type count, const Allocator& alloc = Allocator())
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(alloc) {
    construct_elements(count);
  };

  vector(size_type count, const T& value, const Allocator& alloc = Allocator())
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(alloc) {
    construct_elements(count, value);
  };

  // ------- Copy -------
  vector(const vector& other)
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()) {
    reserve(other.v_capacity);
    copy_elems(other);
  };

  vector(const vector& other, const Allocator& alloc)
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(alloc) {
    reserve(other.v_capacity);
    copy_elems(other);
  };

  // ------- Move -------
  vector(vector&& other) noexcept
      : v_data(other.v_data),
        v_size(other.v_size),
        v_capacity(other.v_capacity),
        v_alloc(other.v_alloc) {
    other.v_data = nullptr;
    other.v_size = 0;
    other.v_capacity = 0;
    other.v_alloc = Allocator();
  };

  vector(vector&& other, const Allocator& alloc)
      : v_data(other.v_data),
        v_size(other.v_size),
        v_capacity(other.v_capacity),
        v_alloc(alloc) {
    other.v_data = nullptr;
    other.v_size = 0;
    other.v_capacity = 0;
    other.v_alloc = Allocator();
  };

  // ------- Initializer list -------
  // vector(std::initializer_list<T> init, const Allocator& alloc =
  // Allocator()){ };

  // ------- Destructors -------
  ~vector() {
    if (v_data != nullptr) {
      v_alloc.deallocate(v_data, v_capacity);
    }
  };

  // ------- Assign -------
  void assign(size_type count, const T& value) {
    construct_elements(count, value);
  };

  // ------- Equal = -------
  reference operator=(const vector& other) {
    if (*this != other) {
      vector copy(other);
      swap(copy);
    }
    return *this;
  };

  vector& operator=(vector&& other) noexcept {
    swap(other);
    return *this;
  };

  // vector& operator=(std::initializer_list<T> ilist);

  allocator_type get_allocator() const noexcept { return v_alloc; };

  // --------------------- ELEMENT ACCESS ---------------------
  reference at(size_type pos) {
    if (pos > v_size || !v_size) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return v_data[pos];
  };

  const_reference at(size_type pos) const {
    if (pos > v_size || !v_size) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return v_data[pos];
  };

  reference operator[](size_type i) { return v_data[i]; };
  const reference operator[](size_type i) const { return v_data[i]; };

  reference front() { return v_data[0]; };
  const_reference front() const { return v_data[0]; };

  reference back() { return v_data[v_size - 1]; };
  const_reference back() const { return v_data[v_size - 1]; };

  T* data() noexcept { return v_data; };
  const T* data() const noexcept { return v_data; };

  // --------------------- CAPACITY ---------------------
  // bool empty() const noexcept {
  // return (begin() == end());
  // };

  size_type size() const noexcept { return v_size; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(v_alloc);
  };

  size_type capacity() const noexcept { return v_capacity; };

  void reserve(size_type n) {
    if (n > v_capacity) {
      T* new_v_data = v_alloc.allocate(n);
      try {
        std::uninitialized_copy(v_data, v_data + v_size, new_v_data);
      } catch (...) {
        v_alloc.deallocate(new_v_data, n);
        throw;
      }
      destroy_data(0, v_size);
      v_alloc.deallocate(v_data, v_capacity);
      v_data = new_v_data;
      v_capacity = n;
    }
  };

  void shrink_to_fit() {
    size_type old_cap = v_capacity;
    destroy_data(v_size, old_cap);
  };

  // --------------------- ITERATORS ---------------------

  // --------------------- MODIFIERS ---------------------
  void resize(size_type count) {
    if (count != v_size) {
      construct_elements(count, 0, v_size);
    }
  };

  void resize(size_type count, const value_type& value) {
    if (count != v_size) {
      construct_elements(count, value, v_size);
    }
  };

  void clear() noexcept { v_size = 0; };

  // iterator insert(const_iterator pos, const T& value);

  // iterator insert(const_iterator pos, T&& value );

  // iterator insert(const_iterator pos, size_type count, const T& value)

  // template< class InputIt >
  // iterator insert(const_iterator pos, InputIt first, InputIt last);

  // iterator insert(const_iterator pos, std::initializer_list<T> ilist);

  // template< class... Args >
  // iterator emplace( const_iterator pos, Args&&... args );

  // iterator erase(const_iterator pos);

  // iterator erase( const_iterator first, const_iterator last );

  // template< class... Args >
  // reference emplace_back( Args&&... args );

  void push_back(const T& value) {
    check_reserve();
    push(value);
  };

  void push_back(T&& value) {
    check_reserve();
    push(std::move(value));
    value.~T();
  };

  void pop_back() {
    --v_size;
    v_data[v_size].~T();
  };

  void swap(vector& other) noexcept {
    std::swap(v_data, other.v_data);
    std::swap(v_size, other.v_size);
    std::swap(v_capacity, other.v_capacity);
    std::swap(v_alloc, other.v_alloc);
  };

 private:
  void construct_elements(size_type count, const T& val = 0,
                          size_type start = 0) {
    check_size(count);
    reserve(count);
    try {
      for (size_t i = start; i < count; ++i) {
        v_alloc.construct(v_data + i, val);
      }
    } catch (...) {
      for (size_t i = start; i < count; ++i) {
        v_alloc.destroy(v_data + i);
      }
      throw;
    }
    v_size = count;
  }

  void push(const T& value) {
    try {
      v_alloc.construct(v_data + v_size, value);
    } catch (...) {
      v_alloc.destroy(v_data + v_size);
      throw;
    }
    ++v_size;
  }

  int check_size(size_type size) const {
    if (max_size() < size) {
      throw std::invalid_argument("std::vector larger than max_size()");
    }
    return true;
  }

  void check_reserve() {
    if ((v_capacity == v_size)) {
      reserve(2 * v_size + 1);
    }
  }

  void copy_elems(const vector& other) {
    for (size_type i = 0; i < other.v_size; ++i) {
      v_data[i] = other.v_data[i];
    }
    v_size = other.v_size;
  }

  void destroy_data(size_type start, size_type end) {
    for (size_type i = start; i < end; ++i) {
      v_alloc.destroy(v_data + i);
      v_capacity--;
    }
  }
};

template <>
class vector<bool> {};

#endif  // CONTAINERS_LIB_VECTOR_H_
