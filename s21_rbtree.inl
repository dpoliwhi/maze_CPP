// #include "s21_rbtree.h"

namespace s21 {

template <class Key, class T>
_NodeRBT<Key, T>::_NodeRBT() : color(BLACK), left(nullptr), right(nullptr), parent(nullptr) {}

template <class Key, class T>
_NodeRBT<Key, T>::_NodeRBT(std::pair<Key, T> pair_data, _NodeRBT<Key, T>* buf)
    : color(RED), left(buf), right(buf), parent(nullptr) {
  data.first = pair_data.first;
  data.second = pair_data.second;
}

template <class Key, class T>
RedBlackTree<Key, T>::RedBlackTree() : _size(0) {
  leaf = new _NodeRBT<Key, T>;
  leaf->color = BLACK;
  leaf->left = nullptr;
  leaf->right = nullptr;
  leaf->parent = nullptr;
  root = leaf;
}

template <class Key, class T>
RedBlackTree<Key, T>::~RedBlackTree() {
  clear_tree();
}

template <class Key, class T>
void RedBlackTree<Key, T>::clear_tree() {
  if (root) {
    if (root != leaf) {
      clear_tree_helper(root);
    }
    delete leaf;
    root = nullptr;
  }
}


template <class Key, class T>
void RedBlackTree<Key, T>::clear_tree_helper(Node root) {
  if (root->left != leaf) {
    clear_tree_helper(root->left);
  }
  if (root->right != leaf) {
    clear_tree_helper(root->right);
  }
  if (root) {
    delete root;
    root = nullptr;
  }
}

template <class Key, class T>
void RedBlackTree<Key, T>::rotate_left(Node x) {
  Node y = x->right;
  /* establish x->right link */
  x->right = y->left;
  if (y->left != leaf) y->left->parent = x;

  /* establish y->parent link */
  if (y != leaf) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
  } else {
    root = y;
  }
  /* link x and y */
  y->left = x;
  if (x != leaf) x->parent = y;
}

template <class Key, class T>
void RedBlackTree<Key, T>::rotate_right(Node x) {
  Node y = x->left;
  /* establish x->left link */
  x->left = y->right;
  if (y->right != leaf) y->right->parent = x;
  /* establish y->parent link */
  if (y != leaf) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
  } else {
    root = y;
  }
  /* link x and y */
  y->right = x;
  if (x != leaf) x->parent = y;
}

template <class Key, class T>
void RedBlackTree<Key, T>::insertFixup(Node x) {
  /* check Red-Black properties */
  while (x != root && x->parent->color == RED) {
    /* we have a violation */
    if (x->parent == x->parent->parent->left) {  // we can move this code in other method to decompose
      Node y = x->parent->parent->right;
      if (y->color == RED) {
        /* uncle is RED */  // we can move this code in other method (same in other case)
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        /* uncle is BLACK */
        if (x == x->parent->right) {
          /* make x a left child */
          x = x->parent;
          rotate_left(x);
        }
        /* recolor and rotate */
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rotate_right(x->parent->parent);
      }
    } else {  // we can move this code in other method to decompose
      /* mirror image of above code */
      Node y = x->parent->parent->left;
      if (y->color == RED) {
        /* uncle is RED */
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        /* uncle is BLACK */
        if (x == x->parent->left) {
          x = x->parent;
          rotate_right(x);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rotate_left(x->parent->parent);
      }
    }
  }
  leaf->parent = find_max_leaf(root, leaf);
  root->color = BLACK;
}

template <class Key, class T>
void RedBlackTree<Key, T>::insertNode(Node new_data) {
  Node child = nullptr;
  Node parent = root;
  while (parent != leaf) {
    child = parent;
    if (new_data->data.first < parent->data.first) {
      parent = parent->left;
    } else {
      parent = parent->right;
    }
  }
  new_data->parent = child;
  if (child == nullptr) {
    root = new_data;
  } else if (new_data->data.first < child->data.first) {
    child->left = new_data;
  } else {
    child->right = new_data;
  }
  if (new_data->parent == nullptr) {
    new_data->color = BLACK;
    return;
  }
  if (new_data->parent->parent == nullptr) {
    return;
  }
}

template <class Key, class T>
void RedBlackTree<Key, T>::deleteFixup(Node ch_node) {
  while (ch_node != root && ch_node->color == BLACK) {
    if (ch_node == ch_node->parent->left) {
      // move in new method - begin
      Node buf = ch_node->parent->right;
      if (buf->color == RED) {
        buf->color = BLACK;
        ch_node->parent->color = RED;
        rotate_left(ch_node->parent);
        buf = ch_node->parent->right;
      }
      if (buf->left->color == BLACK && buf->right->color == BLACK) {
        buf->color = RED;
        ch_node = ch_node->parent;
      } else {
        if (buf->right->color == BLACK) {
          buf->left->color = BLACK;
          buf->color = RED;
          rotate_right(buf);
          buf = ch_node->parent->right;
        }
        buf->color = ch_node->parent->color;
        ch_node->parent->color = BLACK;
        buf->right->color = BLACK;
        rotate_left(ch_node->parent);
        ch_node = root;
      }
      // end
    } else {
      // move in new method - begin
      Node buf = ch_node->parent->left;
      if (buf->color == RED) {
        buf->color = BLACK;
        ch_node->parent->color = RED;
        rotate_right(ch_node->parent);
        buf = ch_node->parent->left;
      }
      if (buf->right->color == BLACK && buf->left->color == BLACK) {
        buf->color = RED;
        ch_node = ch_node->parent;
      } else {
        if (buf->left->color == BLACK) {
          buf->right->color = BLACK;
          buf->color = RED;
          rotate_left(buf);
          buf = ch_node->parent->left;
        }
        buf->color = ch_node->parent->color;
        ch_node->parent->color = BLACK;
        buf->left->color = BLACK;
        rotate_right(ch_node->parent);
        ch_node = root;
      }
      // end
    }
  }
  ch_node->color = BLACK;
}

template <class Key, class T>
void RedBlackTree<Key, T>::deleteNode(Node node, Key key) {
  Node buf = leaf;
  Node child, same_node;
  while (node != leaf) {
    if (node->data.first == key) {
      buf = node;
    }
    if (node->data.first <= key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }
  if (buf == leaf) {
    std::cout << "Key not found in the tree" << std::endl;
    return;
  }
  same_node = buf;
  nodeColor buf_color = same_node->color;
  if (buf->left == leaf) {
    child = buf->right;
    transplant_tree(buf, buf->right);
  } else if (buf->right == leaf) {
    child = buf->left;
    transplant_tree(buf, buf->left);
  } else {
    same_node = find_min_leaf(buf->right, leaf);
    buf_color = same_node->color;
    child = same_node->right;
    if (same_node->parent == buf) {
      child->parent = same_node;
    } else {
      transplant_tree(same_node, same_node->right);
      same_node->right = buf->right;
      same_node->right->parent = same_node;
    }
    transplant_tree(buf, same_node);
    same_node->left = buf->left;
    same_node->left->parent = same_node;
    same_node->color = buf->color;
  }
  delete buf;
  if (buf_color == BLACK) {
    deleteFixup(child);
  }
}

template <class Key, class T>
void RedBlackTree<Key, T>::transplant_tree(Node x, Node z) {
  if (x->parent == nullptr) {
    root = z;
  } else if (x == x->parent->left) {
    x->parent->left = z;
  } else {
    x->parent->right = z;
  }
  z->parent = x->parent;
}

template <class Key, class T>
_NodeRBT<Key, T>* find_min_leaf(_NodeRBT<Key, T>* node, _NodeRBT<Key, T>* leaf) {
  while (node->left != leaf) {
    node = node->left;
  }
  return node;
}

template <class Key, class T>
_NodeRBT<Key, T>* find_max_leaf(_NodeRBT<Key, T>* node, _NodeRBT<Key, T>* leaf) {
  while (node->right != leaf) {
    node = node->right;
  }
  return node;
}

template <class Key, class T>
std::pair<typename RedBlackTree<Key, T>::Node, bool> RedBlackTree<Key, T>::find_by_node(Node node, Key key) {
  if (key == node->data.first) {
    return std::make_pair(node, true);
  } else if (node == leaf) {
    return std::make_pair(node, false);
  }
  if (key < node->data.first) {
    return find_by_node(node->left, key);
  }
  return find_by_node(node->right, key);
}

template <class Key, class T>
std::pair<typename RedBlackTree<Key, T>::Node, bool> RedBlackTree<Key, T>::find_by_key(const Key& key) {
  return find_by_node(root, key);
}

template <class Key, class T>
std::pair<typename RedBlackTree<Key, T>::Node, bool> RedBlackTree<Key, T>::insert_data(
    const value_type& data) {
  Node new_node = new _NodeRBT<Key, T>(data, leaf);
  if (find_by_key(data.first).second == true) {
    delete new_node;
    return std::make_pair(leaf, false);
  }
  insertNode(new_node);
  insertFixup(new_node);
  _size++;
  return std::make_pair(new_node, true);
}

template <class Key, class T>
void RedBlackTree<Key, T>::printTree() {
  if (root) {
    printHelper(this->root, "", true);
  }
}

template <class Key, class T>
void RedBlackTree<Key, T>::printHelper(Node root, std::string indent, bool last) {
  if (root != leaf) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    std::string sColor;
    if (root->color == RED)
      sColor = "RED";
    else if (root->color == BLACK)
      sColor = "BLACK";
    // std::string sColor = root->color;
    std::cout << root->data.second << "(" << sColor << ")" << std::endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}

// Inorder print
template <class Key, class T>
void RedBlackTree<Key, T>::inorder_print(Node node) {
  if (node != leaf) {
    inorder_print(node->left);
    std::cout << node->data.first << " ";
    inorder_print(node->right);
  }
}

template <class Key, class T>
typename RedBlackTree<Key, T>::size_type RedBlackTree<Key, T>::size() {
  return _size;
}

template <class Key, class T>
void RedBlackTree<Key, T>::set_size(size_type size) {
  _size = size;
}


}  // namespace s21

// using namespace s21;
// int main() {
//   s21::RedBlackTree<int, int> one;
//   std::pair<int, int> pair_one = std::make_pair(44, 44);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(33, 33);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(77, 77);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(88, 88);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(99, 99);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(22, 222);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(11, 11);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(5, 5);
//   one.insert_data(pair_one);
//   pair_one = std::make_pair(8, 8);
//   one.insert_data(pair_one);
//   one.printTree();

//   one.deleteNode(one.root, 77);
//   one.printTree();
//   // std::pair<typename RedBlackTree<int, int>::Node, bool> find_node;
//   // find_node = one.find_by_key(21);
//   // find_node.second ? std::cout << "TRUE\n" : std::cout << "FALSE\n";
//   // std::cout << find_node.first->data.second << std::endl;

//   // one.printTree();
//   // one.inorder_print(one.root);
//   return 0;
// }
