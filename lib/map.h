#ifndef CONTAINERS_LIB_MAP_H_
#define CONTAINERS_LIB_MAP_H_

#include <functional>
#include <iostream>

#include "tree.h"

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
  using key_type = Key;
  using mapped_type = T;
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

 public:
  class Node {
   public:
    // Node() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr){};
    Node(value_type data)
        : data(data), parent(nullptr), left(nullptr), right(nullptr){};

  //  private:
    value_type data;
    Node *parent;
    Node *left;
    Node *right;
  };

  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  map() : data_(nullptr), size_(0), alloc_(Allocator()){};

  // map() : map(Compare()) {};

  explicit map(const Compare &comp, const Allocator &alloc = Allocator()){};

  map(const map &other) {
    alloc_ = other.alloc_;
    copy_elements(other);
  };

  map(const map &other, const Allocator &alloc) {
    alloc_ = alloc;
    copy_elements(other);
  };

  map(map &&other) noexcept
      : data_(other.data_), size_(other.size_), alloc_(other.alloc_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.alloc_ = Allocator();
  };

  map(map &&other, const Allocator &alloc) noexcept : map(other) {
    alloc_ = alloc;
    other.alloc_ = Allocator();
  };

  map(std::initializer_list<value_type> init, const Allocator &alloc)
      : map(init, Compare(), alloc) {}

  // ------- Destructors -------
  ~map(){};

  // ------- Copy -------
  map &operator=(const map &other){};

  map &operator=(map &&other) noexcept {};

  map &operator=(std::initializer_list<value_type> ilist){};

  allocator_type get_allocator() const noexcept { return alloc_; };

  // ------- Element access -------
  T &at(const Key &key){};

  const T &at(const Key &key) const {};

  T &operator[](const Key &key) {
    // return iter on find
    return data_[0].data.second;
  };

  T &operator[](Key &&key) {
    // return iter on find
    
    return data_[0].data.second;
  };

  // ------- Iterators -------
  iterator begin() { return iterator(&data_[0]); };
  const_iterator begin() const noexcept { return &data_[0]; };
  const_iterator cbegin() const noexcept { return &data_[0]; };

  iterator end() { return &data_[size_]; };
  const_iterator end() const noexcept { return &data_[size_]; };
  const_iterator cend() const noexcept { return &data_[size_]; };

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
  bool empty() const { return (size_ == 0); }

  size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(alloc_);
  };

  // ------- Modifiers -------
  void clear() noexcept { size_ = 0; };

  // insert
  std::pair<iterator, bool> insert(const value_type &value) {
    return insert_unique(value);
  };

  // insert_or_assign

  template <class... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  template <class... Args>
  iterator emplace_hint(const_iterator hint, Args &&...args);

  // try_emplace

  // erase

  void swap(map &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(alloc_, other.alloc_);
  };

  // extract

  // merge

  // ------- Lookup -------

  // ------- Observers -------
  //  key_comp
  // value_comp

 private:
  Node* data_;
  size_type size_;
  Allocator alloc_;

  void copy_elements(map &&other) {
    int count = 0;
    try {
      for (iterator i = &other.data_[0]; i != &other.data_[other.size_];
           ++i, ++count) {
        alloc_.construct(&data_[count], *i);
      }
    } catch (...) {
      destroy_elements(0, count);
      throw;
    }
  };

  void destroy_elements(size_type start, size_type count) {
    for (size_type i = start; i < count; ++i) {
      alloc_.destroy(data_ + i);
    }
  }

  std::pair<iterator, bool> insert_unique(const value_type& value) {
    bool insert = false;
    if (data_ == nullptr) {
      
      Node* newNode = new Node(value);
      newNode->right = nullptr;
      newNode->left = nullptr;
      newNode->parent = nullptr;
      data_ = newNode;
      ++size_;
      insert = true;
      
    }
    if (!insert) {
      return insert_unique_pos(value.first, value.second);
    }
    return std::pair<iterator, bool>(iterator(begin()), insert);
  };

  std::pair<iterator, bool> insert_unique_pos(Key key, T value) {
    bool insert = false;
    Node* newNode = new Node(value_type(key, value));
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = nullptr;
    ++size_;
    return std::pair<iterator, bool>(iterator(newNode), insert);
  };


};

#endif  // CONTAINERS_LIB_MAP_H_
