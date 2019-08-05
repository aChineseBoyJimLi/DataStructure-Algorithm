//
// Created by jim on 19-7-20.
//

#ifndef TREE_TREE_ADT_H
#define TREE_TREE_ADT_H

#include <cstdio>

// 二叉树节点结构
template <typename Key, typename Value>
struct TreeNode{
    Key key;
    Value value;
    TreeNode* left;
    TreeNode* right;
    TreeNode():left(nullptr), right(nullptr){}
    TreeNode(const Key& k, const Value& v):key(k), value(v){}
};

// 二叉树 ADT
template <typename Key, typename Value>
class BinaryTreeADT{
public:
    virtual ~BinaryTreeADT() = default;
    virtual size_t size() = 0;                                  // 返回节点数
    virtual size_t height() = 0;                                // 返回二叉树层数
    virtual void insert(const Key& k, const Value& v) = 0;      // 二叉检索树的插入，以键值插入
    virtual Value* search(const Key& k) = 0;                    // 以 key 去检索一个节点
    virtual void remove(const Key& k) = 0;                      // 移除一个节点
    virtual void destroy() = 0;                                 // 销毁这棵二叉检索树
    virtual void preTraverse() = 0;                             // 前序遍历，递归实现
    virtual void preTraverseLoop() = 0;                         // 前序遍历，循环实现
    virtual void inTraverse() = 0;                              // 中序遍历，递归实现
    virtual void inTraverseLoop() = 0;                          // 中序遍历，循环实现
    virtual void postTraverse() = 0;                            // 后序遍历，递归实现
    virtual void postTraverseLoop() = 0;                        // 后序遍历，循环实现
    virtual void levelTraverse() = 0;                           // 层级遍历，递归实现
    virtual void levelTraverseLoop() = 0;                       // 层级遍历，循环实现
    virtual bool isFullTree() = 0;                              // 验证是否是满二叉树
    virtual bool isCompleteTree() = 0;                          // 验证是否是完全二叉树
};

#endif //TREE_TREE_ADT_H
