//
// Created by jim on 19-7-20.
//

#ifndef TREE_BINARYSEARCHTREE_H
#define TREE_BINARYSEARCHTREE_H

#include "BinaryTree.h"

// 二叉检索树的实现类
template <typename Key, typename Value>
class BinarySearchTree : public BinaryTree<Key, Value>{
private:
    TreeNode<Key, Value>* root;
    size_t count;

protected:
    TreeNode<Key, Value>* insertHelp(TreeNode<Key, Value>* node, const Key& k, const Value& v);
    TreeNode<Key, Value>* searchHelp(TreeNode<Key, Value>* node, const Key& k);
    TreeNode<Key, Value>* removeHelp(TreeNode<Key, Value>* node, const Key& k);

public:
    BinarySearchTree():root(nullptr), count(0){}
    void insert(const Key& k, const Value& v);
    Value* search(const Key& k);
    void remove(const Key& k);
};



/*
 * 二叉检索树的插入
 */
template <typename Key, typename Value>
TreeNode<Key, Value>* BinarySearchTree<Key, Value>::insertHelp(TreeNode<Key, Value> *node, const Key &k, const Value &v) {
    if(node == nullptr){
        this->count++;
        return new TreeNode<Key, Value>(k, v);
    }
    else{
        // 如果插入节点的值大于根节点的值，插入它的右子树
        if(k > node->key){
            node->right = insertHelp(node->right, k, v);
        }

        if(k == node->key){
            node->value = v;
        }
        // 反之插入左子树
        if(k < node->key){
            node->left = insertHelp(node->left, k, v);
        }
    }

    return node;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key& k, const Value& v) {
    this->root = insertHelp(this->root, k, v);
}


/*
 * 二叉检索树的检索
 */
template <typename Key, typename Value>
TreeNode<Key, Value>* BinarySearchTree<Key, Value>::searchHelp(TreeNode<Key, Value> *node, const Key &k) {
    if(node == nullptr) return nullptr;
    if(k == node->key) return node;
    if(k > node->key) return searchHelp(node->right, k);
    if(k < node->key) return searchHelp(node->left, k);
}
template <typename Key, typename Value>
Value* BinarySearchTree<Key, Value>::search(const Key& k) {
    TreeNode<Key, Value>* tmp = searchHelp(this->root, k);
    if(tmp){
        return const_cast<int*>(&(tmp->value));
    }
    else{
        return nullptr;
    }
}

/*
 * 删除一个节点
 * 如果左节点为空，删除本节点，返回右节点。
 * 如果右节点为空，删除本节点，返回左节点。
 * 如果左右节点都为空，是 1 或者 2 的子情况。
 * 如果左右节点都不为空，找到当前节点的右子树的最小节点，并用这个最小节点替换本节点
 */
template <typename Key, typename Value>
TreeNode<Key, Value>* BinarySearchTree<Key, Value>::removeHelp(TreeNode<Key, Value> *node, const Key &k) {
    if(node == nullptr) return nullptr;

    if(node->key == k){

        // 如果左节点为空，删除本节点，返回右节点。
        if(node->left == nullptr && node->right != nullptr){
            this->count --;
            delete node;
            node = node->right;
            return node;
        }

        // 如果右节点为空，删除本节点，返回左节点。
        if(node->left != nullptr && node->right == nullptr){
            this->count --;
            delete node;
            node = node->left;
            return node;
        }

        // 如果左右节点都为空，是 1 或者 2 的子情况。
        if(node->left == nullptr && node->right == nullptr){
            this->count --;
            delete node;
            node = nullptr;
            return node;
        }

        // 如果左右节点都不为空，找到当前节点的右子树的最小节点，并用这个最小节点替换本节点
        if(node->left != nullptr && node->right != nullptr){
            TreeNode<Key, Value>* nodeRightMin = node->right;
            while(nodeRightMin->left != nullptr){
                nodeRightMin = nodeRightMin->left;
            }

            // swap nodeRightMin and node
            Key tmpKey = nodeRightMin->key;
            Value tmpValue = nodeRightMin->value;

            nodeRightMin->key = node->key;
            nodeRightMin->value = node->value;

            node->key = tmpKey;
            node->value = tmpValue;

            node->right = removeHelp(node->right, nodeRightMin->key);
            return node;
        }


    }

    if(node->key < k){
        node->right = removeHelp(node->right, k);
    }

    if(node->key > k){
        node->left = removeHelp(node->left, k);
    }
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key &k) {
    this->root = removeHelp(this->root, k);
}

#endif //TREE_BINARYSEARCHTREE_H
