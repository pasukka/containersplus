#ifndef SRC_LIB_MAP_H_
#define SRC_LIB_MAP_H_

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

  using BTree = tree<Key, T, Compare, Allocator>;

  using node_type = typename tree<Key, T, Compare, Allocator>::nodePtr;

  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = typename BTree::iterator;
  using const_iterator = const iterator;
  using alloc_traits = std::allocator_traits<Allocator>;
  using iter_pair = std::pair<iterator, bool>;

 public:
  // --------------------- MEMBER FUNCTION ---------------------

  // ------- Constructors -------
  map() : root(){};

  map(const map &other) : root() { root = other.root; };

  map(const map &other, const Allocator &alloc) : root() {
    root = other.root;
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

  // ------- Destructor -------
  ~map(){};

  // ------- Copy -------
  map &operator=(const map &other) {
    root = other.root;
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

  allocator_type get_allocator() const noexcept {
    return root.get_allocator();
  };

  // ------- Element access -------
  T &at(const Key &key) {
    iterator it = find(key);
    if (it == end() || it == nullptr) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  };

  const T &at(const Key &key) const {
    const_iterator it = find(key);
    if (it == end() || it == nullptr) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  };

  T &operator[](const Key &key) {
    iterator it = find(key);
    if (it == end() || it == nullptr) {
      auto result = root.insert_unique(value_type(key, mapped_type()));
      it = result.first;
    }
    return (*it).second;
  };

  T &operator[](Key &&key) {
    iterator it = find(key);
    if (it == end() || it == nullptr) {
      auto result =
          root.insert_unique(value_type(std::move(key), mapped_type()));
      it = result.first;
    }
    return (*it).second;
  };

  // ------- Iterators -------
  iterator begin() { return root.begin(); };
  const_iterator begin() const noexcept { return root.begin(); };
  const_iterator cbegin() const noexcept { return root.cbegin(); };

  iterator end() { return root.end(); };
  const_iterator end() const noexcept { return root.end(); };
  const_iterator cend() const noexcept { return root.cend(); };

  // ------- Capacity -------
  bool empty() const { return (root.size() == 0); }

  size_type size() const noexcept { return root.size(); };

  size_type max_size() const noexcept {
    return alloc_traits::max_size(root.get_allocator());
  };

  // ------- Modifiers -------
  void clear() noexcept { root.clear(); };

  iter_pair insert(const value_type &value) {
    return root.insert_unique(value);
  };

  void insert(std::initializer_list<value_type> ilist) {
    for (auto element : ilist) {
      root.insert_unique(element);
    }
  };

  iter_pair insert(const Key &k, const T &obj) {
    return root.insert_unique(value_type(k, obj));
  };

  iter_pair insert_or_assign(const Key &k, const T &obj) {
    return to_insert_or_assign(value_type(k, obj));
  }

  iter_pair insert_or_assign(Key &&k, T &&obj) {
    return to_insert_or_assign(
        value_type(std::move(k), std::forward<mapped_type>(obj)));
  }

  iterator erase(iterator pos) { return root.erase(pos); };

  iterator erase(const_iterator first, const_iterator last) {
    iterator it_first = iterator(first.getNode());
    iterator it_last = iterator(last.getNode());

    while (it_first != it_last) {
      it_first = erase(it_first);
    }

    return it_last;
  }

  iterator extract(const_iterator position) {
    if (position == end()) {
      return end();
    }
    return root.erase(position);
  }

  iterator extract(const Key &k) {
    iterator it = find(k);
    if (it == end()) {
      return end();
    }
    return root.erase(it);
  }

  void merge(map &other) { root.merge(other.root); };

  void swap(map &other) { root.swap(other.root); };

  // ------- Lookup -------
  iterator find(const Key &key) const {
    return iterator(root.find_node(root.data(), key));
  };

  bool contains(const Key &key) { return (find(key) != nullptr); }

  // ------- Observers -------
  key_compare key_comp() const { return key_compare(); };

 private:
  BTree root;

  iter_pair to_insert_or_assign(const value_type &value) {
    iterator it = find(value.first);
    if (it != end() && it != nullptr) {
      (*it).second = value.second;
      return iter_pair(it, false);
    } else {
      return insert(value);
    }
  }
};

#endif  // SRC_LIB_MAP_H_
