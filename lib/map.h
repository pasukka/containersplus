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
  using iter_pair = std::pair<iterator, bool>;

  using BTree = tree<Key, T, Compare, Allocator>;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  map() : root(){};

  map(const map &other) : root(other.root){};

  map(const map &other, const Allocator &alloc) : root(other.root) {
    root.set_allocator(alloc);
  };

  map(map &&other) noexcept : root(std::move(other.root)){};

  map(map &&other, const Allocator &alloc) noexcept : map(other) {
    root.set_allocator(alloc);
    other.root.set_allocator(Allocator());
  };

  map(std::initializer_list<value_type> init, const Compare &comp = Compare(),
      const Allocator &alloc = Allocator())
      : root(init, comp, alloc){};

  map(std::initializer_list<value_type> init, const Allocator &alloc)
      : map(init, Compare(), alloc){};

  // ------- Destructors -------
  ~map(){};

  // ------- Copy -------
  map &operator=(const map &other) {
    tree copy(other.root);
    root.swap(copy);
    return *this;
  };

  map &operator=(map &&other) noexcept {
    root.swap(other.root);
    return *this;
  };

  map &operator=(std::initializer_list<value_type> ilist) {
    root = ilist;
    return *this;
  };

  allocator_type get_allocator() const noexcept { return root.get_allocator(); };

  // ------- Element access -------
  T &at(const Key &key) {
    iterator it = find(key);
    if (it == nullptr) {
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
    if (it == nullptr) {
      auto result = root.insert_unique(value_type(key, val_type()));
      it = result.first;
    }
    return (*it).second;
  };

  T &operator[](Key &&key) {
    iterator it = find(key);
    if (it == nullptr) {
      auto result = root.insert_unique(value_type(std::move(key), val_type()));
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
  bool empty() const { return (root.size() == 0); }

  size_type size() const noexcept { return root.size(); };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(root.get_allocator());
  };

  // ------- Modifiers -------
  void clear() noexcept {
    root.clear();
    root.set_size(0);
  };

  iter_pair insert(const value_type &value) {
    return root.insert_unique(value);
  };

  void insert(std::initializer_list<value_type> ilist) {
    for (auto element : ilist) {
      root.insert_unique(element);
    }
  };

  template <class M>
  iter_pair insert_or_assign(const Key &k, M &&obj) {
    return to_insert_or_assign(value_type(k, std::forward<val_type>(obj)));
  }

  template <class M>
  iter_pair insert_or_assign(Key &&k, M &&obj) {
    return to_insert_or_assign(
        value_type(std::move(k), std::forward<val_type>(obj)));
  }

  template <class... Args>
  iter_pair emplace(Args &&...args);

  template <class... Args>
  iterator emplace_hint(const_iterator hint, Args &&...args);

  // try_emplace

  // erase
  iterator erase(iterator pos) { root.erase(pos); };

  // extract

  // merge

  // ------- Lookup -------

  iterator find(const Key &key) {
    return iterator(root.find_node(root.data(), key));
  };

  // ------- Observers -------
  key_compare key_comp() const { return key_compare(); };

  // value_comp

 private:
  BTree root;

  iter_pair to_insert_or_assign(const value_type &value) {
    iterator it = find(value.first);
    if (it != nullptr) {
      (*it).second = value.second;
      return iter_pair(it, false);
    } else {
      return insert(value);
    }
  }
};

#endif  // CONTAINERS_LIB_MAP_H_
