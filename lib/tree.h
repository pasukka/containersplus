#ifndef SRC_LIB_TREE_H_
#define SRC_LIB_TREE_H_

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
      // if (data != nullptr) {

      // }
      alloc_.deallocate(data, 1);
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
      return *this;
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

    TreeIterator(nodePtr node) : node_(node) {}

    TreeIterator& operator=(const TreeIterator& other) {
      Base::node_ = other.node_;
      return *this;
    }

    TreeIterator(const TreeIterator& iter) : node_(iter.node_) {}

    reference operator*(void) const { return Base::node_->data; }

    pointer operator->(void) const { return &Base::node_->data; }

    bool operator!=(TreeIterator rhs) const {
      return !(this->node_ == rhs.node_);
    }

    bool operator==(TreeIterator rhs) const {
      return (this->node_ == rhs.node_);
    }

    TreeIterator& operator++() noexcept {
      nodePtr p;
      if (node_->right != nullptr && node_->right->left != node_) {
        node_ = node_->right;
        while (node_->left != nullptr) node_ = node_->left;
      } else {
        p = node_->parent;
        while (p != nullptr && node_ == p->right) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    TreeIterator& operator--() noexcept {
      nodePtr p;
      if (node_->left != nullptr) {
        node_ = node_->left;
        while (node_->right != nullptr && node_->right->left != node_)
          node_ = node_->right;
      } else {
        p = node_->parent;
        while (p != nullptr && node_ == p->left) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    nodePtr getNode() { return node_; }

    nodePtr getNode() const { return node_; }

    void setNode(nodePtr new_node) { std::swap(node_, new_node); }

   protected:
    nodePtr node_;
  };

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
  using const_iterator = const iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using alloc_traits = std::allocator_traits<Allocator>;
  using iter_pair = std::pair<iterator, bool>;

  tree()
      : data_(nullptr),
        root_(nullptr),
        size_(0),
        alloc_(Allocator()),
        key_comp_(Compare()) {
    root_ = create_node();
  };

  tree(const tree& other) noexcept
      : data_(other.data_),
        root_(other.root_),
        size_(other.size_),
        alloc_(other.alloc_),
        key_comp_(other.key_comp_){};

  tree(tree&& other) noexcept
      : data_(other.data_),
        root_(other.root_),
        size_(other.size_),
        alloc_(other.alloc_),
        key_comp_(other.key_comp_) {
    other.data_ = nullptr;
    other.root_ = nullptr;
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

  tree(const Compare& comp, const Allocator& alloc) : tree() {
    clear();
    alloc_ = alloc;
    key_comp_ = comp;
  };

  ~tree() {
    if (data_ != nullptr) {
      clear();
    }
    std::allocator<Node<value_type>> node_alloc;
    node_alloc.deallocate(root_, 1);
  }

  tree& operator=(const tree& other) {
    clear();
    for (auto element : other) {
      insert_unique(element);
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
    while (node != root_ || node != nullptr) {
      if (node == nullptr) {
        break;
      }
      if (node == root_) {
        break;
      }
      if (node->right == root_) {
        root_->left = node->parent;
        if (node->parent != nullptr) {
          node->parent->right = root_;
        }
        nodePtr tmp = node->left;
        alloc_.destroy(&node->data);
        node_alloc.deallocate(node, 1);
        node = tmp;
      } else {
        erase_subtree(node->right);
        nodePtr tmp = node->left;
        alloc_.destroy(&node->data);
        node_alloc.deallocate(node, 1);
        node = tmp;
      }

      --size_;
    }
  }

  void set_node(nodePtr node, nodePtr newNode) {
    if (node->parent->left == node) {
      node->parent->left = newNode;
    } else {
      node->parent->right = newNode;
    }
  }

  void drop_node(nodePtr node) {}

  iterator erase(iterator pos) {
    nodePtr node = pos.getNode();
    iterator iter = end();
    if (node != root_) {
      iter = pos;
      ++iter;
      std::allocator<Node<value_type>> node_alloc;
      nodePtr node_left = node->left;
      nodePtr node_right = node->right;
      if (node_left != nullptr) {
        if (node != root_) {
          node->parent->left = node_left;
        }
        if (node->parent == root_) {
          data_ = node_left;
        }
        if (node_right != nullptr) {
          nodePtr most_right_of_left_branch = node_left;
          while (most_right_of_left_branch->right != nullptr &&
                 most_right_of_left_branch->right != root_) {
            most_right_of_left_branch = most_right_of_left_branch->right;
          }
          most_right_of_left_branch->right = node_right;
          if (node_right != nullptr)
            node_right->parent = most_right_of_left_branch;
          set_node(node, node_left);
        }
        node_left->parent = node->parent;
      } else if (node_left == nullptr && node_right == nullptr) {
        set_node(node, nullptr);
      } else {
        if (node_right == root_) {
          node_right->left = node->parent;
        } else {
          node_right->parent = node->parent;
        }
        node->parent->right = node_right;
        if (node == data_) data_ = node_right;
      }
      alloc_.destroy(&pos.getNode()->data);
      node_alloc.deallocate(pos.getNode(), 1);
      --size_;
    }
    return iter;
  }

  nodePtr most_left() const {
    nodePtr left_node = data_;
    if (left_node != nullptr) {
      while (left_node->left != nullptr) {
        left_node = left_node->left;
      }
    }
    return left_node;
  }

  iterator begin() { return iterator(most_left()); };
  const_iterator begin() const noexcept { return const_iterator(most_left()); };
  const_iterator cbegin() const noexcept {
    return const_iterator(most_left());
  };

  iterator end() { return iterator(root_); };
  const_iterator end() const noexcept { return const_iterator(root_); };
  const_iterator cend() const noexcept { return const_iterator(root_); };

  nodePtr find_node(nodePtr node, const Key& key) const {
    if (node == root_ || node == nullptr) {
      return node;
    } else if (key == node->data.first) {
      return node;
    }
    if (key < node->data.first) {
      return find_node(node->left, key);
    }
    return find_node(node->right, key);
  }

  bool exists(const Key& key) {
    return (iterator(find_node(data_, key)) != end() &&
            find_node(data_, key) != nullptr);
  }

  nodePtr create_node() {
    std::allocator<Node<value_type>> node_alloc;
    nodePtr newNode = nullptr;
    try {
      newNode = node_alloc.allocate(1);
    } catch (...) {
      node_alloc.deallocate(newNode, 1);
    }
    newNode->right = data_;
    newNode->left = data_;
    newNode->parent = nullptr;
    return newNode;
  };

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
      newNode->parent = root_;
      newNode->right = root_;
      data_ = newNode;
      ++size_;
      insert = true;
      root_->left = data_;
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
    nodePtr node_ent = data_;
    nodePtr prev = data_;
    int left = 0;
    while (node_ent != root_ && node_ent != nullptr) {
      if (key < node_ent->data.first) {
        prev = node_ent;
        node_ent = node_ent->left;
        left = 1;
      } else {
        prev = node_ent;
        node_ent = node_ent->right;
        left = 0;
      }
    }
    if (node_ent == root_) {
      root_->left = newNode;
      newNode->right = root_;
    }

    if (left == 1) {
      prev->left = newNode;
    } else {
      prev->right = newNode;
    }
    newNode->parent = prev;
    ++size_;
    insert = true;
    iterator it = iterator(newNode);
    return iter_pair(it, insert);
  }

  void merge(tree& other) {
    iterator it_other = other.begin();

    while (it_other != other.end()) {
      insert_unique(*it_other);
      ++it_other;
    }

    other.clear();
  };

  void swap(tree& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(alloc_, other.alloc_);
    std::swap(key_comp_, other.key_comp_);
  };

  nodePtr data() const noexcept { return data_; };
  nodePtr root() const noexcept { return root_; }
  size_type size() const noexcept { return size_; };
  void set_size(size_type size) noexcept { size_ = size; };
  void set_allocator(const Allocator& alloc) noexcept { alloc_ = alloc; };

  allocator_type get_allocator() const noexcept { return alloc_; };
  key_compare_type get_key_comp_() const noexcept { return alloc_; };

 private:
  nodePtr data_;
  nodePtr root_;
  size_type size_;
  allocator_type alloc_;
  key_compare_type key_comp_;
};

#endif  // SRC_LIB_TREE_H_
