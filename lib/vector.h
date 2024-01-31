#ifndef SRC_LIB_VECTOR_H_
#define SRC_LIB_VECTOR_H_

#include <stdint.h>

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
  using allocator_type = Allocator;

  // typedef typename alloc_traits::value_type allocator_type;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  vector() noexcept(noexcept(Allocator()))
      : data_(nullptr), size_(0), capacity_(0), alloc_(Allocator()){};

  explicit vector(size_type count, const Allocator& alloc = Allocator())
      : vector() {
    alloc_ = alloc;
    construct_elements(count);
  };

  vector(size_type count, const T& value, const Allocator& alloc = Allocator())
      : vector() {
    alloc_ = alloc;
    construct_elements(count, value);
  };

  // ------- Copy -------
  vector(const vector& other) : vector() {
    reserve(other.capacity_);
    copy_elems(other);
  };

  vector(const vector& other, const Allocator& alloc) : vector() {
    alloc_ = alloc;
    reserve(other.capacity_);
    copy_elems(other);
  };

  // ------- Move -------
  vector(vector&& other) noexcept
      : data_(other.data_),
        size_(other.size_),
        capacity_(other.capacity_),
        alloc_(other.alloc_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    other.alloc_ = Allocator();
  };

  vector(vector&& other, const Allocator& alloc) : vector(other) {
    alloc_ = alloc;
    other.alloc_ = Allocator();
  };

  // ------- Initializer list -------
  vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
      : vector() {
    alloc_ = alloc;
    *this = init;
  };

  template <typename InputIt>
  using RequireInputIterator = typename std::enable_if<std::is_convertible<
      typename std::iterator_traits<InputIt>::iterator_category,
      std::input_iterator_tag>::value>::type;

  template <class InputIt, typename = RequireInputIterator<InputIt>>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : vector() {
    alloc_ = alloc;
    size_type count = difference_type(last - first);
    check_size(count);
    reserve(count);
    size_type pos = 0;
    try {
      for (; pos < count; ++pos) {
        alloc_.construct(data_ + pos, *first);
        ++first;
      }
    } catch (...) {
      destroy_elements(pos);
      throw;
    }
    size_ = count;
  }

  // ------- Destructors -------
  ~vector() {
    if (data_ != nullptr) {
      alloc_.deallocate(data_, capacity_);
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
    size_ = ilist.size();
    return *this;
  };

  allocator_type get_allocator() const noexcept { return alloc_; };

  // --------------------- ELEMENT ACCESS ---------------------
  reference at(size_type pos) {
    if (pos > size_ || !size_) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return data_[pos];
  };

  const_reference at(size_type pos) const {
    if (pos > size_ || !size_) {
      throw std::out_of_range(
          "vector::_M_range_check: __n (which is" + std::to_string(pos) +
          ">= this->size() (which is " + std::to_string(pos) + ")");
    }
    return data_[pos];
  };

  reference operator[](size_type i) { return data_[i]; };
  const reference operator[](size_type i) const { return data_[i]; };

  reference front() { return data_[0]; };
  const_reference front() const { return data_[0]; };

  reference back() { return data_[size_ - 1]; };
  const_reference back() const { return data_[size_ - 1]; };

  T* data() noexcept { return data_; };
  const T* data() const noexcept { return data_; };

  // --------------------- CAPACITY ---------------------
  bool empty() const noexcept { return (begin() == end()); };

  size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(alloc_);
  };

  size_type capacity() const noexcept { return capacity_; };

  void reserve(size_type n = 1) {
    if (n > capacity_) {
      pointer new_data_ = nullptr;
      try {
        new_data_ = alloc_.allocate(n);
        std::uninitialized_copy(data_, data_ + size_, new_data_);
      } catch (...) {
        alloc_.deallocate(new_data_, n);
        destroy_data(0, size_);
        throw;
      }
      swap_data(new_data_, n);
    }
  };

  void shrink_to_fit() {
    size_type old_cap = capacity_;
    destroy_data(size_, old_cap);
  };

  // --------------------- ITERATORS ---------------------
  iterator begin() noexcept { return data_; };
  const_iterator begin() const noexcept { return data_; };
  const_iterator cbegin() const noexcept { return data_; };

  iterator end() noexcept { return data_ + size_; };
  const_iterator end() const noexcept { return data_ + size_; };
  const_iterator cend() const noexcept { return data_ + size_; };

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
  void clear() noexcept { size_ = 0; };

  void resize(size_type count) {
    if (count != size_) {
      construct_elements(count, 0, size_);
    }
  };

  void resize(size_type count, const value_type& value) {
    if (count != size_) {
      construct_elements(count, value, size_);
    }
  };

  iterator insert(const_iterator pos, const T& value) {
    return to_insert(pos, value);
  };

  iterator insert(const_iterator pos, T&& value) {
    return to_insert(pos, std::move(value));
  };

  iterator insert(const_iterator pos, size_type count, const T& value) {
    if (max_size() < count + size_ || max_size() < count) {
      throw std::length_error("vector::_M_fill_insert");
    }
    return to_insert(pos, value, count);
  };

  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    size_type count = difference_type(last - first);
    size_type start_vector = pos - cbegin();
    size_type all_size = start_vector + (cend() - pos);
    pointer new_data_ = alloc_.allocate(all_size + count);
    size_type i = 0;
    for (; i < start_vector; ++i) {
      create_new_element(new_data_, i, i + 1, data_[i]);
    }
    for (size_type j = 0; j < count; ++j, ++i) {
      create_new_element(new_data_, i, i + 1, *first);
      ++first;
    }
    i -= count;
    for (; i < all_size; ++i) {
      create_new_element(new_data_, i + count, i + count + 1, data_[i]);
    }
    swap_data(new_data_, all_size);
    size_ += count;
    return data_ + start_vector;
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  };

  iterator erase(const_iterator pos) {
    size_type end_of_vector = cend() - pos;
    size_type start = pos - cbegin();
    for (size_type j = 0; j < end_of_vector - 1; ++j, ++start) {
      create_new_element(data_, start, start + 1, data_[start + 1]);
    }
    size_ -= 1;
    start = pos - cbegin();
    return data_ + start;
  };

  iterator erase(const_iterator first, const_iterator last) {
    size_type count = last - first;
    size_type start = first - cbegin();
    for (size_type j = start; j < size_ - count; ++j) {
      create_new_element(data_, j, j + 1, *(first + count));
      ++first;
    }
    size_ -= count;
    return data_ + start;
  };

  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    return insert(pos, std::move(std::forward<Args>(args)...));
  }

  template <class... Args>
  reference emplace_back(Args&&... args) {
    auto old_size = size_;
    push_back(std::move(std::forward<Args>(args)...));
    reference element = data_[old_size];
    return element;
  }

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
    --size_;
    data_[size_].~T();
  };

  void swap(vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(alloc_, other.alloc_);
  };

 private:
  T* data_;
  size_type size_;
  size_type capacity_;
  Allocator alloc_;

  void destroy_elements(size_type count, size_type start = 0) {
    for (size_type i = start; i < count; ++i) {
      alloc_.destroy(data_ + i);
    }
  };

  void construct_elements(size_type count, const T& val = 0,
                          size_type start = 0) {
    check_size(count);
    reserve(count);
    create_new_element(data_, start, count, val);
    size_ = count;
  }

  void create_new_element(pointer data, size_type start, size_type count,
                          const T& value) {
    try {
      for (size_type i = start; i < count; ++i) {
        alloc_.construct(data + i, value);
      }
    } catch (...) {
      destroy_elements(count, start);
      throw;
    }
  }

  void push(const T& value) {
    try {
      alloc_.construct(data_ + size_, value);
    } catch (...) {
      alloc_.destroy(data_ + size_);
      throw;
    }
    ++size_;
  }

  int check_size(size_type size) const {
    if (max_size() < size) {
      throw std::length_error("std::vector larger than max_size()");
    }
    return true;
  }

  void check_reserve() {
    if ((capacity_ == size_)) {
      reserve(2 * size_ + 1);
    }
  }

  void copy_elems(const vector& other) {
    for (size_type i = 0; i < other.size_; ++i) {
      data_[i] = other.data_[i];
    }
    size_ = other.size_;
  }

  void destroy_data(size_type start, size_type end) {
    for (size_type i = start; i < end; ++i) {
      alloc_.destroy(data_ + i);
      --capacity_;
    }
  }

  void swap_data(pointer new_data_, size_type n) {
    destroy_data(0, size_);
    alloc_.deallocate(data_, capacity_);
    data_ = new_data_;
    capacity_ = n;
  }

  iterator to_insert(const_iterator pos, const T& value, size_type count = 1) {
    size_type start_vector = pos - cbegin();
    size_type all_size = start_vector + (cend() - pos);
    pointer new_data_ = alloc_.allocate(all_size + count);
    size_type i = 0;
    for (; i < start_vector; ++i) {
      create_new_element(new_data_, i, i + 1, data_[i]);
    }
    for (size_type j = 0; j < count; ++j, ++i) {
      create_new_element(new_data_, i, i + 1, value);
    }
    i -= count;
    for (; i < all_size; ++i) {
      create_new_element(new_data_, i + count, i + count + 1, data_[i]);
    }
    swap_data(new_data_, all_size);
    size_ += count;
    return data_ + start_vector;
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

#endif  // SRC_LIB_VECTOR_H_
