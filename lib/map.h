#ifndef CONTAINERS_LIB_MAP_H_
#define CONTAINERS_LIB_MAP_H_

#include <functional>
#include <iostream>

#include "tree.h"

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
  using key_type = Key;
  using val_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = value_type &;
  using const_reference = const value_type &;

  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using alloc_traits = std::allocator_traits<Allocator>;

  using BTree = tree<Key, T, Compare, Allocator>;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  map() : root(){};

  map(const map &other) : root(other.root){};

  map(const map &other, const Allocator &alloc) : root(other.root) {
    root.alloc_ = alloc;
  };

  map(map &&other) noexcept : root(other.root){};

  map(map &&other, const Allocator &alloc) noexcept : map(other) {
    root.alloc_ = alloc;
    other.root.alloc_ = Allocator();
  };

  // map(std::initializer_list<value_type> init, const Allocator &alloc)
  //     : map(init, Compare(), alloc) {}

  // ------- Destructors -------
  ~map(){};

  // ------- Copy -------
  map &operator=(const map &other) {
    map copy(other);
    swap(copy);
  };

  map &operator=(map &&other) noexcept {
    swap(other);
    return *this;
  };

  map &operator=(std::initializer_list<value_type> ilist){};

  allocator_type get_allocator() const noexcept { return root.alloc_; };

  // ------- Element access -------
  T &at(const Key &key) {
    iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  };

  const T &at(const Key &key) const {
    const_iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  };

  T &operator[](const Key &key) {
    iterator it = find(key);
    if (it == end()) {
      auto result = insert(value_type(key, val_type()));
      it = result.first;
    }
    return (*it).second;
  };

  T &operator[](Key &&key) {
    iterator it = find(key);
    if (it == end()) {
      auto result = insert(value_type(std::move(key), val_type()));
      it = result.first;
    }
    return (*it).second;
  };

  // ------- Iterators -------
  iterator begin() { return root.begin(); };
  const_iterator begin() const noexcept { return root.begin(); };
  const_iterator cbegin() const noexcept { return root.begin(); };

  iterator end() { return root.end(); };
  const_iterator end() const noexcept { return root.end(); };
  const_iterator cend() const noexcept { return root.end(); };

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
  bool empty() const { return (root.size_ == 0); }

  size_type size() const noexcept { return root.size_; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(root.alloc_);
  };

  // ------- Modifiers -------
  void clear() noexcept { root.size_ = 0; };

  // insert
  std::pair<iterator, bool> insert(const value_type &value) {
    return root.insert_unique(value);
  };

  // insert_or_assign

  template <class... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  template <class... Args>
  iterator emplace_hint(const_iterator hint, Args &&...args);

  // try_emplace

  // erase

  // extract

  // merge

  // ------- Lookup -------

  iterator find(const Key &key) {
    return iterator(root.find_node(root.data_, key));
  };

  // ------- Observers -------
  //  key_comp
  // value_comp

 private:
  BTree root;

  // void copy_elements(map &&other) {
  //   int count = 0;
  //   try {
  //     for (iterator i = &other.data_[0]; i != &other.data_[other.size_];
  //          ++i, ++count) {
  //       root.alloc_.construct(&data_[count], *i);
  //     }
  //   } catch (...) {
  //     destroy_elements(0, count);
  //     throw;
  //   }
  // };

  // void destroy_elements(size_type start, size_type count) {
  //   for (size_type i = start; i < count; ++i) {
  //     root.alloc_.destroy(data_ + i);
  //   }
  // }
};

#endif  // CONTAINERS_LIB_MAP_H_
