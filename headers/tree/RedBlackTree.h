//
// Created by jim on 19-7-20.
//

#ifndef TREE_REDBLACKTREE_H
#define TREE_REDBLACKTREE_H

#include "BinarySearchTree.h"

// 红黑树的节点类
typedef enum  {RED, BLACK} color_set; // 红黑节点的枚举

template<typename Key, typename Value>
struct RBNode : public TreeNode<Key, Value>{
    color_set color;              // 节点颜色
    RBNode<Key, Value>* parent;   // 父节点指针
    RBNode<Key, Value>* left;     // 左子点指针
    RBNode<Key, Value>* right;    // 右子点指针

    RBNode(){
        color = RED;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    bool onleft(){                // 判断自身是否是左子节点
        if(parent->left == this)
            return true;
        else
            return false;
    }
    bool onright(){               // 判断自身是否是右子节点
        if(parent->right == this)
            return true;
        else
            return false;
    }


    // 返回叔叔节点的颜色
    color_set getUncleColor(){
        if(parent->onleft()){
            if(parent->parent->right == nullptr)
                return BLACK;
            else
                return parent->parent->right->color;
        }
        else{
            if(parent->parent->left == nullptr)
                return BLACK;
            else
                return parent->parent->left->color;
        }
    }

    // 设置叔叔节点的颜色
    void setUncleColor(color_set c){
        if(parent->onleft()){
            parent->parent->right->color = c;
        }
        else{
            parent->parent->left->color = c;
        }
    }
};

// 红黑树的实现类
/*
 * 红黑树的性质
 * 性质一: 每个结点或者是黑色，或者是白色
 * 性质二: 根结点是黑色
 * 性质三: 每个叶节点（NIL）是黑色 （这里的叶子结点，是指为空的叶子结点，有的教材也称其为外部节点）
 * 性质四: 如果一个结点是红色，则它的子节点必须是黑色
 * 性质五: 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点
 */
template <typename Key, typename Value>
class RedBlackTree : public BinarySearchTree<Key, Value>{
private:
    RBNode<Key, Value>* root;
    size_t count;

    void LeftRotate(RBNode<Key, Value>* node);
    void RightRotate(RBNode<Key, Value>* node);

    RBNode<Key, Value>* insertHelp(RBNode<Key, Value>* node, RBNode<Key, Value>* parent,
                                   const Key& key, const Value& value);
    void insertRepair(RBNode<Key, Value>* node);
public:


    RedBlackTree():root(nullptr), count(0){}
    void insert(const Key& k, const Value& v);   // 插入一个节点
};


/*
 * 左旋转
 *       |                                  |
 *       8                                  10
 *      / \                                / \
 *     7  10     -- 对节点 8 左旋 -->       8  11
 *        / \                             / \
 *       9  11                           7   9
 *
 * 1. 将 8 的父节点的左或右节点设为 10
 * 2. 将 10 的左节点设为 8 的右节点
 * 3. 将 10 的左节点设为 8
 */

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::LeftRotate(RBNode<Key, Value>* node) {
    if(node == nullptr || node->right == nullptr)
        return;

    RBNode<Key, Value>* nodeRight = node->right;

    // 先设置 node 的父节点
    if(node->parent != nullptr){
        if(node->onleft()){
            node->parent->left = nodeRight;
        }
        else{
            node->parent->right = nodeRight;
        }
    }
    nodeRight->parent = node->parent;

    // 再设置 node 节点的右节点
    node->right = nodeRight->left;
    nodeRight->left->parent = node;

    // 在设置 nodeRight 的左节点
    nodeRight->left = node;
    node->parent = nodeRight;

}

/*
 * 右旋转
 *
 *         |                                |
 *         8                                6
 *        / \                              / \
 *       6   9    -- 对节点 8 右旋 -->      5  8
 *      / \                                  / \
 *     5   7                                7   9
 * 1. 将 8 的父节点的左或右节点设为 6
 * 2. 将 6 的右节点设为 8 的左节点
 * 3. 将 6 的右节点设为 8
 */
template<typename Key, typename Value>
void RedBlackTree<Key, Value>::RightRotate(RBNode<Key, Value> *node) {
    if(node == nullptr || node->left == nullptr)
        return;
    RBNode<Key, Value>* nodeLeft = node->left;

    // 先设置 node 的父节点
    if(node->parent != nullptr){
        if(node->onleft()){
            node->parent->left = nodeLeft;
        }
        else{
            node->parent->right = nodeLeft;
        }
    }
    nodeLeft->parent = node->parent;

    // 再设置 node 节点的左节点
    node->left = nodeLeft->right;
    nodeLeft->right->parent = node;

    // 在设置 nodeLeft 节点的右节点
    nodeLeft->right = node;
    node->parent = nodeLeft;
}

/*
 * 红黑的插入
 * 1. 按照正常的二叉检索来插入
 * 2. 将插入节点至为红色
 * 3. 通过旋转和重新着色等方法修正该树，使之重新成为一棵红黑树
 *
 * 插入一个节点后, 可能有如下五种情况
 * 1. 如果插入的是根节点，由于原树是空树，此情况会违反性质 2，因此直接把此节点涂为黑色
 * 2. 如果插入的节点的父节点是黑色，由于此不会违反性质 2 和 性质 4，红黑树没有被破坏，所以此时什么也不做
 * 3. 插入修复情况1：如果当前节点 z 的父节点是红色且祖父节点的另一个子节点（叔叔节点）是红色
 * 4. 插入修复情况2：当前节点 z 的父节点是红色，叔叔节点是黑色，当前节点是其父节点的右子节点
 * 5. 插入修复情况3：当前节点 z 的父节点是红色，叔叔节点是黑色，当前节点是其父节点的左子节点
 */
template<typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key &k, const Value &v) {
    root = insertHelp(root, nullptr, k, v);
}

template<typename Key, typename Value>
RBNode<Key, Value>* RedBlackTree<Key, Value>::insertHelp(RBNode<Key, Value> *node, RBNode<Key, Value> *parent,
                                                        const Key &key, const Value &value)
{
    // 一棵正常的二叉检索树的插入
    if(node == nullptr){
        node = new RBNode<Key, Value>;
        node->key = key;
        node->value = value;
        node->parent = parent;
        count++;
    }
    else{
        if(key > node->key){
            node->right = insertHelp(node->right, node, key, value);
        }
        if(key == node->key){
            node->value = value;
        }
        if(key < node->key){
            node->left = insertHelp(node->left, node, key, value);
        }
        node->parent = parent;
    }

    // 将节点至为红色
    node->color = RED;

    // 对插入节点进行修正
    insertRepair(node);

    return node;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::insertRepair(RBNode<Key, Value> *node) {

    // 情况一: 如果插入的是根节点，由于原树是空树，此情况会违反性质 2，因此直接把此节点涂为黑色
    if(node->parent == nullptr){
        node->color = BLACK;
        return;
    }

    // 情况二: 如果插入的节点的父节点是黑色，由于此不会违反性质 2 和 性质 4，红黑树没有被破坏，所以此时什么也不做
    if(node->parent->color == BLACK){
        return;
    }

    // 插入修复情况：如果当前节点 z 的父节点是红色
    if(node->parent->color == RED){
        // 叔叔节点的颜色是也是红色
        // 修复情况一: 叔叔节点是红色
        if(node->getUncleColor() == RED){
            // 修复方案
            node->parent->color = BLACK; // 父亲节点至黑
            node->setUncleColor(BLACK);  // 叔叔节点至黑
            node->parent->parent->color = RED;  // 祖父节点至红
            insertRepair(node->parent->parent); // 从祖父节点继续执行修复
        }

        // 修复情况二, 三: 叔叔节点是黑色
        else{
            // 修复情况二: 当前节点是其父节点的右子节点
            if(node->parent->onright()){
                node = node->parent;
                LeftRotate(node);
                insertRepair(node);
            }

            // 修复情况三: 当前节点是其父节点的左子节点
            else{
                node->parent->color = BLACK;  // 父亲节点至黑
                node->parent->parent->color = RED;   // 祖父节点至红
                RightRotate(node->parent->parent);  // 祖父节点右旋转
                return; // 只要完成修复情况二, 也就完成了红黑树的修复
            }
        }
    }



}


#endif //TREE_REDBLACKTREE_H
