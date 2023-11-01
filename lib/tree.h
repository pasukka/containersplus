#include <functional>
#include <iostream>

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class tree {
 public:
  using key_type = Key;
  // using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  // using difference_type = std::ptrdiff_t;
  using key_compare_type = Compare;
  using allocator_type = Allocator;
  // using reference = value_type&;
  // using const_reference = const value_type&;

  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using alloc_traits = std::allocator_traits<Allocator>;
  using iter_pair = std::pair<iterator, bool>;

  class Node {
   public:
    value_type data;
    Node* parent;
    Node* left;
    Node* right;

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

  tree()
      : data_(nullptr), size_(0), alloc_(Allocator()), key_comp_(Compare()){};

  tree(const tree& other)
      : data_(other.data_),
        size_(other.size_),
        alloc_(other.alloc_),
        key_comp_(other.key_comp_){};

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

  ~tree() {}

  tree& operator=(const tree& other) {
    tree copy(other);
    swap(copy);
  };

  tree& operator=(std::initializer_list<value_type> ilist) {
    clear();
    for (auto element : ilist) {
      insert_unique(element);
    }
    return *this;
  };

  void clear() {
    erase(iterator(data_));
    data_ = nullptr;
    size_ = 0;
  };

  void erase(iterator pos){
    
  };

  iterator begin() { return iterator(data_); };

  iterator end() { return iterator(data_ + size_); };

  bool null(Node* node) {
    return ((node->left == nullptr) && (node->right == nullptr));
  };

  Node* find_node(Node* node, const Key& key) {
    if ((node == nullptr) || key == node->data.first) {
      return node;
    }
    if (key < node->data.first) {
      return find_node(node->left, key);
    }
    return find_node(node->right, key);
  }

  bool exists(const Key& key) {
    return (iterator(find_node(data_, key)) != nullptr);
  }

  Node* create_node(const value_type& value) {
    std::allocator<Node> node_alloc;
    Node* newNode = nullptr;
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
    Node* newNode = create_node(value);
    Key key = value.first;
    iterator it = begin();
    if (size_ == 0) {
      data_ = newNode;
      ++size_;
      insert = true;
      it = begin();
    } else if (!exists(key)) {
      return insert_new_unique(value);
    }
    return iter_pair(it, insert);
  };

  iter_pair insert_new_unique(const value_type& value) {
    bool insert = false;
    Node* newNode = create_node(value);
    Key key = value.first;
    Node* current = data_;
    Node* prev = data_;
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

  Node* data() const noexcept { return data_; };
  size_type size() const noexcept { return size_; };
  void set_size(size_type size) noexcept { size_ = size; };

  allocator_type get_allocator() const noexcept { return alloc_; };
  key_compare_type get_key_comp_() const noexcept { return alloc_; };

 private:
  Node* data_;
  size_type size_;
  allocator_type alloc_;
  key_compare_type key_comp_;
};