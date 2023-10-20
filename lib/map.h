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
  using const_reverse_iterator= std::reverse_iterator<const_iterator>;


  map(): map(Compare()) {}
};

#endif  // CONTAINERS_LIB_MAP_H_
