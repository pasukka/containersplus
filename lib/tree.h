#include <functional>
#include <iostream>

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class tree {
  template <typename value_type>
  class Node {
   public:
    using nodePtr = Node<value_type>*;

    value_type data;
    nodePtr parent;
    nodePtr left;
    nodePtr right;

    Node() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr){};
    Node(value_type data)
        : data(data), parent(nullptr), left(nullptr), right(nullptr){};

    ~Node() {
      if (data != nullptr) {
        alloc_.deallocate(data, 1);
      }
    };

    Node(const Node& other)
        : data(other.data),
          parent(other.parent),
          left(other.left),
          right(other.right){};

    Node& operator=(const Node& other) {
      std::swap(data, other.data);
      std::swap(parent, other.parent);
      std::swap(left, other.left);
      std::swap(right, other.right);
    };
  };

  template <typename value_type>
  class TreeIterator {
  public:
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    using nodePtr = Node<value_type>*;
    using Base = TreeIterator<value_type>;
    using Self = TreeIterator<value_type>;

    explicit TreeIterator(nodePtr node) : node_(node) {}
    TreeIterator(const Self& it) : Node<value_type>(it.node_) {}

    TreeIterator& operator=(const TreeIterator& other) {
      Base::node_ = other.node_;
      return *this;
    }

    reference operator*(void) const { return Base::node_->value; }

    pointer operator->(void) const { return &Base::node_->value; }

   protected:
    nodePtr node_;

  };
  // tree<int, int, std::less<int>, std::allocator<std::pair<const int, int> > >::TreeIterator<std::pair<const int, int> >

  template <typename valueType>
  bool operator!=(tree<Key, T, Compare, Allocator>::TreeIterator<valueType>& lhs,
                  tree<Key, T, Compare, Allocator>::TreeIterator<valueType>& rhs) {
  return !(lhs == rhs);
  }

 public:
  using key_type = Key;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  using key_compare_type = Compare;
  using allocator_type = Allocator;

  using pointer = value_type*;
  using nodePtr = Node<value_type>*;
  using const_pointer = const value_type*;
  using iterator = TreeIterator<value_type>;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using alloc_traits = std::allocator_traits<Allocator>;
  using iter_pair = std::pair<iterator, bool>;

  tree()
      : data_(nullptr), size_(0), alloc_(Allocator()), key_comp_(Compare()){};

  tree(tree&& other) noexcept
      : data_(other.data_),
        size_(other.size_),
        alloc_(other.alloc_),
        key_comp_(other.key_comp_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.alloc_ = Allocator();
    other.key_comp_ = Compare();
  };

  tree(std::initializer_list<value_type> init, const Compare& comp = Compare(),
       const Allocator& alloc = Allocator())
      : tree() {
    clear();
    alloc_ = alloc;
    key_comp_ = comp;
    for (auto element : init) {
      insert_unique(element);
    }
  };

  ~tree() {
    if (data_ != nullptr) {
      clear();
    }
  }

  tree& operator=(const tree& other) {
    clear();
    for (size_t i = 0; i < other.size_; ++i) {
      insert_unique(other.data_->data);
    }
    return *this;
  };

  tree& operator=(std::initializer_list<value_type> ilist) {
    clear();
    for (auto element : ilist) {
      insert_unique(element);
    }
    return *this;
  };

  void clear() {
    if (data_ != nullptr) {
      erase_subtree(data_);
    }
    data_ = nullptr;
    size_ = 0;
  };

  void erase_subtree(nodePtr node) {
    std::allocator<Node<value_type>> node_alloc;
    while (node != nullptr) {
      erase_subtree(node->right);
      auto tmp = node->left;
      alloc_.destroy(&node->data);
      node_alloc.deallocate(node, 1);
      node = tmp;
    }
  }

  void erase(iterator pos){

  };

  iterator begin() { return iterator(data_); };
  const_iterator begin() const noexcept { return iterator(data_); };
  const_iterator cbegin() const noexcept { return iterator(data_); };

  iterator end() { return iterator(data_ + size_); };
  const_iterator end() const noexcept { return iterator(data_ + size_); };
  const_iterator cend() const noexcept { return iterator(data_ + size_); };

  nodePtr find_node(nodePtr node, const Key& key) {
    if ((node == nullptr) || key == node->data.first) {
      return node;
    }
    if (key < node->data.first) {
      return find_node(node->left, key);
    }
    return find_node(node->right, key);
  }

  bool exists(const Key& key) {
    return (iterator(find_node(data_, key)) != end());  // != nullptr
  }

  nodePtr create_node(const value_type& value) {
    std::allocator<Node<value_type>> node_alloc;
    nodePtr newNode = nullptr;
    try {
      newNode = node_alloc.allocate(1);
    } catch (...) {
      node_alloc.deallocate(newNode, 1);
    }
    try {
      alloc_.construct(&newNode->data, value);
    } catch (...) {
      alloc_.destroy(&newNode->data);
    }
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = nullptr;
    return newNode;
  };

  iter_pair insert_unique(const value_type& value) {
    bool insert = false;
    Key key = value.first;
    iterator it = begin();
    if (size_ == 0) {
      nodePtr newNode = create_node(value);
      data_ = newNode;
      ++size_;

      // for (size_t i = 0; i < size_; ++i) {
      //   printf("\n%d %d\n", data_->data.first, data_->data.second);
      // }

      insert = true;
      it = begin();
    } else if (!exists(key)) {
      return insert_new_unique(value);
    }
    return iter_pair(it, insert);
  };

  iter_pair insert_new_unique(const value_type& value) {
    bool insert = false;
    nodePtr newNode = create_node(value);
    Key key = value.first;
    nodePtr current = data_;
    nodePtr prev = data_;
    int left = 0;
    while (current != nullptr) {
      if (key < current->data.first) {
        prev = current;
        current = current->left;
        left = 1;
      } else if (key >= current->data.first) {
        prev = current;
        current = current->right;
        left = 0;
      }
    }
    if (left == 1) {
      prev->left = newNode;
    } else {
      prev->right = newNode;
    }
    ++size_;
    insert = true;
    iterator it = iterator(newNode);
    return iter_pair(it, insert);
  }

  void swap(tree& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(alloc_, other.alloc_);
    std::swap(key_comp_, other.key_comp_);
  };

  nodePtr data() const noexcept { return data_; };
  size_type size() const noexcept { return size_; };
  void set_size(size_type size) noexcept { size_ = size; };
  void set_allocator(const Allocator& alloc) noexcept { alloc_ = alloc; };

  allocator_type get_allocator() const noexcept { return alloc_; };
  key_compare_type get_key_comp_() const noexcept { return alloc_; };

 private:
  nodePtr data_;
  size_type size_;
  allocator_type alloc_;
  key_compare_type key_comp_;
};