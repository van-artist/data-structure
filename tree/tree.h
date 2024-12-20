#ifndef TREE_H
#define TREE_H

#include <vector>
#include <stack>
#include <queue>

template <typename T>
struct TreeNode
{
    T value;
    TreeNode<T> *parent;
    std::vector<TreeNode<T> *> children;
    TreeNode(const T &value, TreeNode<T> *parent = nullptr) : value(value), parent(parent) {}

    void addChild(TreeNode<T> *child)
    {
        child->parent = this;
        children.push_back(child);
    }
};

template <typename T>
using TreeNodePtr = TreeNode<T> *;

template <typename T>
class Tree
{
private:
    TreeNodePtr<T> root;
    void deleteTree(TreeNodePtr<T> root);

public:
    Tree(TreeNodePtr<T> root) : root(root) {}
    Tree() : root(nullptr) {}
    ~Tree()
    {
        deleteTree(this->root);
    }

    std::vector<T> dfsTraversal(TreeNodePtr<T> root) const;
    std::vector<T> bfsTraversal(TreeNodePtr<T> root) const;
};

template <typename T>
void Tree<T>::deleteTree(TreeNodePtr<T> root)
{
    if (root == nullptr)
        return;
    for (auto child : root->children)
    {
        deleteTree(child);
    }
    delete root;
}

template <typename T>
std::vector<T> Tree<T>::dfsTraversal(TreeNodePtr<T> root) const
{
    std::vector<T> output;
    if (root == nullptr)
        return output; // 空指针检查
    std::stack<TreeNodePtr<T>> tasks;
    tasks.push(root);
    while (!tasks.empty())
    {
        TreeNodePtr<T> currentNodePtr = tasks.top();
        tasks.pop();
        output.push_back(currentNodePtr->value);

        // 倒序添加孩子节点以保证左侧优先
        for (auto it = currentNodePtr->children.rbegin(); it != currentNodePtr->children.rend(); ++it)
        {
            tasks.push(*it);
        }
    }
    return output;
}

template <typename T>
std::vector<T> Tree<T>::bfsTraversal(TreeNodePtr<T> root) const
{
    std::vector<T> output;
    if (root == nullptr)
        return output; // 空指针检查
    std::queue<TreeNodePtr<T>> tasks;
    tasks.push(root);
    while (!tasks.empty())
    {
        TreeNodePtr<T> currentNodePtr = tasks.front();
        tasks.pop();
        output.push_back(currentNodePtr->value);

        for (const auto &child : currentNodePtr->children)
        {
            tasks.push(child);
        }
    }
    return output;
}

#endif // TREE_H
