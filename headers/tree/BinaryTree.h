//
// Created by jim on 19-7-20.
//

#ifndef TREE_BINARYTREE_H
#define TREE_BINARYTREE_H

#include "Tree_ADT.h"
#include <iostream>
#include <stack>
#include <queue>

// 普通二叉树，链表实现类
// 未实现 insert，search，remove 函数，依然是一个抽象类
template <typename Key, typename Value>
class BinaryTree : public BinaryTreeADT<Key, Value>{
private:
    size_t count;   // 二叉树的节点个数
    TreeNode<Key, Value>* root; // 根节点

protected:

    int heightHelp(TreeNode<Key, Value>* node);
    void destroyHelp(TreeNode<Key, Value>* node);
    void preTraverseHelp(TreeNode<Key, Value>* node);
    void inTraverseHelp(TreeNode<Key, Value>* node);
    void postTraverseHelp(TreeNode<Key, Value>* node);
    bool isFullTreeHelp(TreeNode<Key, Value>* node);
    bool isCompleteTreeHelp(TreeNode<Key, Value>* node);

public:

    // 构造函数
    BinaryTree():count(0), root(nullptr){}

    // 析构函数
    ~BinaryTree(){
        destroy();
    }

    size_t size();
    size_t height();
    void destroy();
    void preTraverse();
    void preTraverseLoop();
    void inTraverse();
    void inTraverseLoop();
    void postTraverse();
    void postTraverseLoop();
    void levelTraverse();
    void levelTraverseLoop();
    bool isFullTree();
    bool isCompleteTree();
};



/*
 * 二叉树节点的个数
 */
template <typename Key, typename Value>
size_t BinaryTree<Key, Value>::size() {
    return count;
}

/*
 * 二叉树的高度
 */
template <typename Key, typename Value>
size_t BinaryTree<Key, Value>::height() {
    heightHelp(root);
}

template <typename Key, typename Value>
int BinaryTree<Key, Value>::heightHelp(TreeNode<Key, Value> *node) {
    if(node == nullptr) return 0;
    int hl = heightHelp(node->left);    // 计算节点的左子树的高度
    int hr = heightHelp(node->right);   // 计算节点的右子树的高度

    if(hl > hr)
        return ++hl;
    else
        return ++hr;
}


/*
 * 二叉树的销毁
 * 后序遍历释放整棵树的内存
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::destroy() {
    destroyHelp(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::destroyHelp(TreeNode<Key, Value> *node) {
    if(node == nullptr) return;
    destroyHelp(node->left);
    destroyHelp(node->right);
    node->left = nullptr;
    node->right = nullptr;
    delete node;
    node = nullptr;
}


/*
 * 二叉树的前序遍历，递归实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::preTraverse() {
    preTraverseHelp(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::preTraverseHelp(TreeNode<Key, Value> *node) {
    if(node==nullptr) return;
    std::cout << node->key << ":" << node->value << std::endl; // 访问该节点，该操作可以通过函数指针传入
    preTraverseHelp(node->left);
    preTraverseHelp(node->right);
}


/*
 * 二叉树的前序遍历，循环实现
 * 1)输出节点P，然后将其入栈，再看P的左孩子是否为空；
 * 2)若P的左孩子不为空，则置P的左孩子为当前节点，重复1）的操作；
 * 3)若P的左孩子为空，则将栈顶节点出栈，但不输出，并将出栈节点的右孩子置为当前节点，看其是否为空；
 * 4)若不为空，则循环至1）操作；
 * 5)如果为空，则继续出栈，但不输出，同时将出栈节点的右孩子置为当前节点，看其是否为空，重复4）和5）操作；
 * 6)直到当前节点P为NULL并且栈空，遍历结束。
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::preTraverseLoop() {
    TreeNode<Key, Value>* currNode = root;      // 当前节点
    std::stack<TreeNode<Key, Value>*> stack;    // 临时栈

    if(currNode == nullptr){
        std::cout << "二叉树为空" << std::endl;
        return;
    }

    while(currNode || stack.size()!=0){
        std::cout << currNode->key << ":" << currNode->value << std::endl; // 访问该节点，该操作可以通过函数指针传入

        stack.push(currNode);
        currNode = currNode->left;

        while( currNode == nullptr && stack.size() !=0){    // 若currNode的左孩子为空，就得开始访问currNode的右孩子了
            currNode = stack.top();
            stack.pop();
            currNode = currNode->right;
        }

    }
}


/*
 * 二叉树的中序遍历，递归实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::inTraverse(){
    inTraverseHelp(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::inTraverseHelp(TreeNode<Key, Value> *node) {
    if (node == nullptr) return;
    inTraverseHelp(node->left);
    std::cout << node->key << ":" << node->value << std::endl; // 访问该节点，该操作可以通过函数指针传入
    inTraverseHelp(node->right);
}

/*
 * 二叉树的中序遍历，循环实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::inTraverseLoop() {

    TreeNode<Key, Value>* currNode = root;      // 当前节点

    std::stack<TreeNode<Key, Value>*> stack;    // 临时栈

    if(currNode == nullptr){
        std::cout << "二叉树为空" << std::endl;
        return;
    }

    while(currNode || stack.size()!=0){
        stack.push(currNode);
        currNode = currNode->left;

        while(currNode == nullptr && stack.size()!=0){
            currNode = stack.top();
            std::cout << currNode->key << ":" << currNode->value << std::endl; // 访问该节点，该操作可以通过函数指针传入
            stack.pop();
            currNode = currNode->right;
        }
    }

}

/*
 * 二叉树的后序遍历，递归实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::postTraverse() {
    postTraverseHelp(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::postTraverseHelp(TreeNode<Key, Value> *node) {
    if(node==nullptr)return;
    postTraverseHelp(node->left);
    postTraverseHelp(node->right);
    std::cout << node->key << ":" << node->value << std::endl; // 访问该节点，该操作可以通过函数指针传入
}

/*
 * 二叉树的后序遍历，循环实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::postTraverseLoop() {

    TreeNode<Key, Value>* currNode = root;      // 当前节点

    std::stack<TreeNode<Key, Value>*> stack;    // 临时栈

    if(currNode == nullptr){
        std::cout << "二叉树为空" << std::endl;
        return;
    }

    while(currNode || stack.size() != 0){
        stack.push(currNode);
        currNode = currNode->left;

        if(currNode == nullptr){
            currNode = stack.top();
            while(currNode->right == nullptr && stack.size() != 0){
                std::cout << currNode->key << ":" << currNode->value << std::endl; // 访问该节点，该操作可以通过函数指针传入
                stack.pop();
                currNode = stack.top()->right;
                if(currNode)
                    break;
            }
        }
    }

}


/*
 * 二叉树的层级遍历，递归实现
 * https://www.cnblogs.com/QoQian/p/5438278.html
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::levelTraverse() {

}

/*
 * 二叉树的层级遍历，循环实现
 */
template <typename Key, typename Value>
void BinaryTree<Key, Value>::levelTraverseLoop() {
    if(root == nullptr) return;

    std::queue<TreeNode<Key, Value>*> treeNodesQueue;
    treeNodesQueue.push(root);  // 将根节点入队列

    while(treeNodesQueue.size() != 0){
        TreeNode<Key, Value>* node = treeNodesQueue.front();
        std::cout << node->key << ":" << node->value << std::endl; // 打印该节点
        treeNodesQueue.pop();

        // 将队列头的节点的左右子节点压入队列
        if(node->left != nullptr)
            treeNodesQueue.push(node->left);
        if(node->right != nullptr)
            treeNodesQueue.push(node->right);
    }
}


/* 满二叉树的验证
 * 如果一棵二叉树所有节点都有零个或两个子节点, 那么这棵树为满二叉树.
 * 反过来说, 满二叉树中不存在只有一个子节点的节点.
 */
template <typename Key, typename Value>
bool BinaryTree<Key, Value>::isFullTree() {
    return isFullTreeHelp(root);
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::isFullTreeHelp(TreeNode<Key, Value> *node) {
    if(node == nullptr)
        return true;
    if(node->left == nullptr && node->right != nullptr){
        return false;
    }
    if(node->left != nullptr && node->right == nullptr){
        return false;
    }
    return isFullTreeHelp(node->left) && isFullTreeHelp(node->right);
}


/*
 * 完全二叉树的验证
 * 完全二叉树：若设二叉树的深度为 h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边
 * 思路是按层序遍历，检查每层是否满足完全二叉树的性质
 */
template <typename Key, typename Value>
bool BinaryTree<Key, Value>::isCompleteTree() {
    if(root == nullptr) return false;
    return isCompleteTreeHelp(root);
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::isCompleteTreeHelp(TreeNode<Key, Value> *node) {
    std::queue<TreeNode<Key, Value>*> queue;
    queue.push(node);
    bool flag = false;  // 用一个标志位记录上一个节点是否为空
    while(!queue.empty()){
        TreeNode<Key, Value>* tmp = queue.front();
        queue.pop();

        if(flag && (tmp->left || tmp->right))
            return false; // 如果这里的flag是true，证明在之前的出现了右节点为空的情况，如果之后还有节点，不满足完全二叉树的定义
        if(tmp->left)
            queue.push(tmp->left);
        else
            flag = true;
        if(tmp->right){
            if(flag)
                return false;   // 左节点为空，右节点非空，不满足完全二叉树的定义
            else
                queue.push(tmp->right);
        }
        else
            flag = true;
    }
    return true;
}

#endif //TREE_BINARYTREE_H
