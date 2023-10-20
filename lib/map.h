#ifndef CONTAINERS_LIB_MAP_H_
#define CONTAINERS_LIB_MAP_H_

#include <functional>
#include <iostream>

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
  using key_type = Key;
  using mapped_type = T;
  using valuetype = std::pair<const Key, T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = value_type&;
  using const_reference = const value_type&;

  using pointer = std::allocator_traits<Allocator>::pointer;
  using const_pointer = std::allocator_traits<Allocator>::const_pointer;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  map() : data_(nullptr), size_(0), capacity_(0), alloc_(Allocator()) {}
  
  map() : map(Compare()) {}

  explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) {};

  // ------- Destructors -------

  // ------- Copy -------

  map& operator=(const map& other) {};

  map& operator=(map&& other) noexcept {};

  map& operator=(std::initializer_list<value_type> ilist) {};

  allocator_type get_allocator() const noexcept { return alloc_; };

  // ------- Element access -------

  T& at(const Key& key){};

  const T& at(const Key& key) const {

  };

  T& operator[](const Key& key){};

  T& operator[](Key&& key){};

  // ------- Iterators -------

  iterator begin() { return &data_[0]; }
  const_iterator begin() const noexcept { return &data_[0]; };
  const_iterator cbegin() const noexcept { return &data_[0]; };

  iterator end() { return &data_[size_]; }
  const_iterator end() const noexcept {return &data_[size_]};
  const_iterator cend() const noexcept {return &data_[size_]};

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

  // ------- Capacity -------

  bool empty() { return (size_ == 0); }

  size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(alloc_);
  };

  // ------- Modifiers -------

  void clear() noexcept { size_ = 0; };

  void swap(map& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(alloc_, other.alloc_);
  };

  // ------- Lookup -------

  // ------- Observers -------
  //  key_comp
  // value_comp

 private:
  pointer data_;
  size_type size_;
  size_type capacity_;
  Allocator alloc_;
};

#endif  // CONTAINERS_LIB_MAP_H_
