#ifndef CONTAINERS_LIB_VECTOR_H_
#define CONTAINERS_LIB_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using alloc_traits = std::allocator_traits<Allocator>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using difference_type = std::ptrdiff_t;

  typedef typename alloc_traits::value_type allocator_type;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  vector() noexcept(noexcept(Allocator()))
      : v_data(nullptr), v_size(0), v_capacity(0), v_alloc(Allocator()){};

  explicit vector(size_type count, const Allocator& alloc = Allocator())
      : vector() {
    v_alloc = alloc;
    construct_elements(count);
  };

  vector(size_type count, const T& value, const Allocator& alloc = Allocator())
      : vector() {
    v_alloc = alloc;
    construct_elements(count, value);
  };

  // ------- Copy -------
  vector(const vector& other) : vector() {
    reserve(other.v_capacity);
    copy_elems(other);
  };

  vector(const vector& other, const Allocator& alloc) : vector() {
    v_alloc = alloc;
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

  vector(vector&& other, const Allocator& alloc) : vector(other) {
    v_alloc = other.v_alloc;
    other.v_alloc = Allocator();
  };

  // ------- Initializer list -------
  vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
      : vector() {
    v_alloc = alloc;
    *this = init;
  };

  template <typename InputIt>
  using RequireInputIterator = typename std::enable_if<std::is_convertible<
      typename std::iterator_traits<InputIt>::iterator_category,
      std::input_iterator_tag>::value>::type;

  template <class InputIt, typename = RequireInputIterator<InputIt>>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : vector() {
    v_alloc = alloc;
    size_type count = difference_type(last - first);
    check_size(count);
    reserve(count);
    size_type pos = 0;
    try {
      for (; pos < count; ++pos) {
        v_alloc.construct(v_data + pos, *first);
        ++first;
      }
    } catch (...) {
      destroy_elements(pos);
      throw;
    }
    v_size = count;
  }

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
  vector& operator=(const vector& other) {
    // if (this != other) {
    vector copy(other);
    swap(copy);
    // }
    return *this;
  };

  vector& operator=(vector&& other) noexcept {
    swap(other);
    return *this;
  };

  vector& operator=(std::initializer_list<T> ilist) {
    reserve(ilist.size());
    size_type pos = 0;
    for (auto element : ilist) {
      construct_elements(pos + 1, element, pos);
      ++pos;
    }
    v_size = ilist.size();
    return *this;
  };

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
  bool empty() const noexcept { return (begin() == end()); };

  size_type size() const noexcept { return v_size; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(v_alloc);
  };

  size_type capacity() const noexcept { return v_capacity; };

  void reserve(size_type n = 1) {
    if (n > v_capacity) {
      T* new_v_data = v_alloc.allocate(n);
      try {
        std::uninitialized_copy(v_data, v_data + v_size, new_v_data);
      } catch (...) {
        v_alloc.deallocate(new_v_data, n);
        throw;
      }
      swap_data(new_v_data, n);
    }
  };

  void shrink_to_fit() {
    size_type old_cap = v_capacity;
    destroy_data(v_size, old_cap);
  };

  // --------------------- ITERATORS ---------------------
  iterator begin() noexcept { return v_data; };
  const_iterator begin() const noexcept { return v_data; };
  const_iterator cbegin() const noexcept { return v_data; };

  iterator end() noexcept { return v_data + v_size; };
  const_iterator end() const noexcept { return v_data + v_size; };
  const_iterator cend() const noexcept { return v_data + v_size; };

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); };
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); };

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  };

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  };

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  };

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  };

  // --------------------- MODIFIERS ---------------------
  void clear() noexcept { v_size = 0; };

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

  iterator insert(const_iterator pos, const T& value) {
    return to_insert(pos, value);
  };

  iterator insert(const_iterator pos, T&& value) {
    return to_insert(pos, std::move(value));
  };

  iterator insert(const_iterator pos, size_type count, const T& value) {
    if (max_size() < count + v_size || max_size() < count) {
      throw std::length_error("vector::_M_fill_insert");
    }
    return to_insert(pos, value, count);
  };

  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    size_type count = difference_type(last - first);
    size_type start_vector = pos - cbegin();
    size_type all_size = start_vector + (cend() - pos);
    pointer new_v_data = v_alloc.allocate(all_size + count);
    size_type i = 0;
    make_start(new_v_data, &i, start_vector);
    for (size_type j = 0; j < count; ++j, ++i) {
      new_v_data[i] = *first;
      ++first;
    }
    make_end(new_v_data, &i, count, all_size);
    swap_data(new_v_data, all_size);
    v_size += count;
    return v_data + start_vector;
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  };

  // template< class... Args >
  // iterator emplace( const_iterator pos, Args&&... args );

  iterator erase(const_iterator pos) {
    size_type end_of_vector = cend() - pos;
    size_type start = pos - cbegin();
    for (size_type j = 0; j < end_of_vector - 1; ++j, ++start) {
      v_data[start] = v_data[start + 1];
    }
    v_size -= 1;
    start = pos - cbegin();
    return v_data + start;
  };

  iterator erase(const_iterator first, const_iterator last) {
    size_type count = last - first;
    size_type start = first - cbegin();
    for (size_type j = start; j < v_size - count; ++j) {
      v_data[j] = *(first + count);
      ++first;
    }
    v_size -= count;
    return v_data + start;
  };

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
  T* v_data;
  size_type v_size;
  size_type v_capacity;
  Allocator v_alloc;

  void destroy_elements(size_type count, size_type start = 0) {
    for (size_type i = start; i < count; ++i) {
      v_alloc.destroy(v_data + i);
    }
  };

  void construct_elements(size_type count, const T& val = 0,
                          size_type start = 0) {
    check_size(count);
    reserve(count);
    try {
      for (size_type i = start; i < count; ++i) {
        v_alloc.construct(v_data + i, val);
      }
    } catch (...) {
      destroy_elements(count, start);
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
      throw std::length_error("std::vector larger than max_size()");
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
      --v_capacity;
    }
  }

  void swap_data(pointer new_v_data, size_type n) {
    destroy_data(0, v_size);
    v_alloc.deallocate(v_data, v_capacity);
    v_data = new_v_data;
    v_capacity = n;
  }

  iterator to_insert(const_iterator pos, const T& value, size_type count = 1) {
    size_type start_vector = pos - cbegin();
    size_type all_size = start_vector + (cend() - pos);
    pointer new_v_data = v_alloc.allocate(all_size + count);
    size_type i = 0;
    make_start(new_v_data, &i, start_vector);
    for (size_type j = 0; j < count; ++j, ++i) {
      new_v_data[i] = value;
    }
    make_end(new_v_data, &i, count, all_size);
    swap_data(new_v_data, all_size);
    v_size += count;
    return v_data + start_vector;
  }

  void make_start(pointer new_v_data, size_type* pos, size_type start_vector) {
    for (; *pos < start_vector; ++*pos) {
      new_v_data[*pos] = v_data[*pos];
    }
  }

  void make_end(pointer new_v_data, size_type* pos, size_type count,
                size_type all_size) {
    *pos -= count;
    for (; *pos < all_size; ++(*pos)) {
      new_v_data[*pos + count] = v_data[*pos];
    }
  }
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  bool output = true;
  if (lhs.size() != rhs.size()) {
    output = false;
  } else {
    for (size_t i = 0; i < lhs.size(); ++i) {
      if (lhs[i] != rhs[i]) {
        output = false;
      }
    }
  }
  return output;
};

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
};

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  bool output = false;
  if (lhs.size() < rhs.size()) {
    output = true;
  } else {
    for (size_t i = 0; i < lhs.size(); ++i) {
      if (lhs[i] < rhs[i]) {
        output = true;
      }
    }
  }
  return output;
};

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs > rhs);
};

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs || lhs == rhs);
};

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
};

template <>
class vector<bool> {};

#endif  // CONTAINERS_LIB_VECTOR_H_
