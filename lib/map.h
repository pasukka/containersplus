#ifndef CONTAINERS_LIB_MAP_H_
#define CONTAINERS_LIB_MAP_H_

#include <iostream>

namespace pmr {
template <class Key, class T, class Compare = std::less<Key>>
using map = std::map<Key, T, Compare,
                     std::pmr::polymorphic_allocator<std::pair<const Key, T>>>;
}
using valuetype = std::pair<const Key, T>;
using size_type = std::size_t;

#endif  // CONTAINERS_LIB_MAP_H_
