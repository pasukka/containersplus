#include <functional>
#include <iostream>

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class tree {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = value_type&;
  using const_reference = const value_type&;

  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using alloc_traits = std::allocator_traits<Allocator>;

  class Node {
   public:
    value_type data;
    Node* parent;
    Node* left;
    Node* right;

    Node() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr){};
    Node(value_type data)
        : data(data), parent(nullptr), left(nullptr), right(nullptr){};
  };

  tree() : data_(nullptr), size_(0), alloc_(Allocator()){};

  tree(const tree& other)
      : data_(other.data_), size_(other.size_), alloc_(other.alloc_){};

  tree(tree&& other) noexcept
      : data_(other.data_), size_(other.size_), alloc_(other.alloc_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.alloc_ = Allocator();
  };

  ~tree() {}  // TODO

  tree& operator=(const tree& other) {
    tree copy(other);
    swap(copy);
  };

  iterator begin() { return iterator(data_); };

  iterator end() { return iterator(data_ + size_); };

  size_type size() const noexcept { return size_; };

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

  bool exists(const Key& key) { return (find_node(data_, key) == nullptr); }

  std::pair<iterator, bool> insert_unique(const value_type& value) {
    bool insert = false;
    Node* newNode = new Node(value);
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = nullptr;
    Key key = value.first;
    iterator it = begin();
    if (data_ == nullptr) {
      data_ = newNode;
      ++size_;
      insert = true;
      it = begin();
    } else {  // TODO if (!exists(key))
      Node* current = data_;
      Node* prev = data_;
      int left;
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
      it = iterator(newNode);
    }
    return std::pair<iterator, bool>(it, insert);
  };

  void swap(tree& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(alloc_, other.alloc_);
  };

  //  private:
  Node* data_;
  size_type size_;
  Allocator alloc_;
};