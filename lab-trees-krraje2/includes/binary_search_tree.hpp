#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tree_node.hpp"

/******************************************************
 * CLASS DEFINITIONS + HELPER FUNCTION DECLARATIONS
 ******************************************************/

template <typename T>
class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree& lhs) = delete;
  BinarySearchTree<T>& operator=(const BinarySearchTree& lhs) = delete;
  ~BinarySearchTree();
  TreeNode<T>* InsertNode(const T& data);
  TreeNode<T>* DeleteNode(const T& data);
  int GetHeight() const;
  TreeNode<T>* GetRoot() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const BinarySearchTree<U>& bst);

private:
  TreeNode<T>* root_;

  TreeNode<T>* InsertNode(TreeNode<T>* node, const T& data);

  TreeNode<T>* DeleteNode(TreeNode<T>* node, const T& data);

  int GetHeight(TreeNode<T>* node) const;
  void Clear(TreeNode<T>* node);
  void AddPrintableData(TreeNode<T>* node,
                        std::vector<std::string>& output,
                        int left,
                        int top,
                        int width) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst);

/******************************************************
 * MEMBER FUNCTION + HELPER FUNCTION DEFINITIONS
 ******************************************************/

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root_(nullptr) {}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(const T& data) {
  root_ = InsertNode(root_, data);
  return root_;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(TreeNode<T>* node, const T& data) {
  // return the inserted node
  if (node == nullptr) {
    node = new TreeNode<T>(data);
    return node;
  }

  if (data < node->data) {
    node->left = InsertNode(node->left, data);
  } else {
    node->right = InsertNode(node->right, data);
  }
  return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(const T& data) {
  if (root_ == nullptr) {
    return nullptr;
  }

  root_ = DeleteNode(root_, data);
  return root_;
}
template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(TreeNode<T>* node, const T& data) {
  // return the appropriate successor/children
  if (node == nullptr) {
    return node;
  }
  if (data < node->data) {
    node->left = DeleteNode(node->left, data);
  } else if (data > node->data) {
    node->right = DeleteNode(node->right, data);
  } else {
    // leaf case
    if (node->left == nullptr && node->right == nullptr) {
      return nullptr;
    }
    // one child only
    // right child
    if (node->left == nullptr) {
      auto right_child = node->right;
      delete node;
      return right_child;
    }
    // left child
    if (node->right == nullptr) {
      auto left_child = node->left;
      delete node;
      return left_child;
    }

    // if two children, return succesor
    auto succesor = node->right;
    // needs to check if null is first, otherwise could yield error for succesor -> left
    while (succesor != nullptr && succesor->left != nullptr) {
      succesor = succesor->left;
    }
    node->data = succesor->data;
    // must call the function to delete everything possibly to the right
    node->right = DeleteNode(node->right, succesor->data);
    delete succesor;
    succesor = nullptr;
  }
  return node;
}

template <typename T>
void BinarySearchTree<T>::Clear(TreeNode<T>* node) {
  if (node) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear(root_);
}

template <typename T>
int BinarySearchTree<T>::GetHeight() const {
  return GetHeight(root_);
}

template <typename T>
int BinarySearchTree<T>::GetHeight(TreeNode<T>* node) const {
  if (node == nullptr) {
    return -1;
  }

  return 1 + std::max(GetHeight(node->left), GetHeight(node->right));
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::GetRoot() const {
  return root_;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst) {
  size_t root_height = bst.GetHeight() + 1;

  std::vector<std::string> output(2 * root_height - 1);
  for (size_t i = 0; i < output.size(); i++) {
    output[i] = std::string((4 << root_height) + 1, ' ');
  }

  bst.AddPrintableData(bst.root_, output, 0, 0, (4 << root_height) - 3);

  for (size_t i = 0; i < output.size(); i++) {
    os << output[i] << std::endl;
  }
  return os;
}

template <typename T>
void BinarySearchTree<T>::AddPrintableData(TreeNode<T>* node,
                                           std::vector<std::string>& output,
                                           int left,
                                           int top,
                                           int curr_width) const {
  std::stringstream ss;
  std::string str;
  ss << node->data;
  ss >> str;

  int left_start_shift = 1 - (str.length() - 1) / 2;
  for (size_t i = 0;
       i < str.length() && left + curr_width / 2 + i < output[top].length();
       i++) {
    output[top][left + curr_width / 2 + left_start_shift + i] = str[i];
  }

  int branchOffset = (curr_width + 3) >> 3;

  int center = left + curr_width / 2;
  int leftcenter = left + (curr_width / 2 - 1) / 2;
  int rightcenter = left + curr_width / 2 + 2 + (curr_width / 2 - 1) / 2;

  if (node->left) {
    int branch_pos = center - branchOffset + 1;
    for (int pos = center + left_start_shift - 2; pos > branch_pos; pos--) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '/';
    for (int pos = branch_pos - 1; pos > leftcenter + 2; pos--) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->left, output, left, top + 2, curr_width / 2 - 1);
  }

  if (node->right) {
    int branch_pos = center + branchOffset + 1;
    for (int pos = center + left_start_shift + str.length() + 1;
         pos < branch_pos;
         pos++) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '\\';
    for (int pos = branch_pos + 1; pos < rightcenter; pos++) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->right,
                     output,
                     left + curr_width / 2 + 2,
                     top + 2,
                     curr_width / 2 - 1);
  }
}

#endif  // BINARYSEARCHTREE_HPP