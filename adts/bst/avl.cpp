#pragma once

#include "bst.cpp"
#include <iostream>
#include <string>

template <class T>
class avl : public bst<T>
{
private:
    struct node
    {
        T data;
        node *left = nullptr;
        node *right = nullptr;
        int height = 1;
    };

    node *root = nullptr;
    int count = 0;

    int height(node *n)
    {
        if (!n) return 0;
        return n->height;
    }

    int max(int a, int b)
    {
        if (a > b) return a;
        return b;
    }

    node *insert(node *root, T data)
    {
        if (!root)
        {
            count++;
            node *n = new node;
            n->data = data;
            return n;
        }

        if (data < root->data)
        {
            root->left = insert(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
        else
        {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));
        root = balance(root);

        return root;
    }

    node *balance(node *root)
    {
        if (!root) return root;

        int rootBF = height(root->left) - height(root->right);

        if (rootBF == 2)
        {
            int leftBF = height(root->left->left) - height(root->left->right);

            if (leftBF >= 0)
            {
                root = rightRot(root);
            }
            else
            {
                root = leftRightRot(root);
            }
        }
        else if (rootBF == -2)
        {
            int rightBF = height(root->right->left) - height(root->right->right);

            if (rightBF <= 0)
            {
                root = leftRot(root);
            }
            else
            {
                root = rightLeftRot(root);
            }
        }

        return root;
    }

    node *rightRot(node *z)
    {
        /*
                z               y
               / \             / \
              y   t1  ----->  x   z
             / \                 / \
            x   t2             t2   t1
        */
        node *y = z->left;
        node *y_r = y->right;

        y->right = z;
        z->left = y_r;

        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    node *leftRot(node *z)
    {
        /*
                z               y
               / \             / \
              t1   y  ----->  z   x
                  / \        / \
                 t2  x     t1   t2
        */
        node *y = z->right;
        node *y_l = y->left;

        y->left = z;
        z->right = y_l;

        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    node *rightLeftRot(node *z)
    {
        /*
           z                    z                    x
          / \                  / \                  / \
         t1  y   ----->       t1  x   ----->       z   y
            / \                  / \              / \ / \
           x  t4                t2  y            t1 t2 t3 t4
          / \                      / \
         t2  t3                   t3  t4
        */
        z->right = rightRot(z->right);
        return leftRot(z);
    }

    node *leftRightRot(node *z)
    {
        /*
           z                    z                    x
          / \                  / \                  / \
         y   t4   ----->      x   t4   ----->      y   z
        / \                  / \                  / \ / \
       t1  x                y  t3               t1 t2 t3 t4
          / \              / \
         t2 t3            t1 t2
        */
        z->left = leftRot(z->left);
        return rightRot(z);
    }

    node *minNode(node *root)
    {
        while (root && root->left)
        {
            root = root->left;
        }
        return root;
    }

    node *remove(node *root, T data)
    {
        if (!root) return root;

        if (data < root->data)
        {
            root->left = remove(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = remove(root->right, data);
        }
        else
        {
            // caso 1: sin hijos
            if (!root->left && !root->right)
            {
                delete root;
                count--;
                return nullptr;
            }

            // caso 2: un solo hijo
            if (!root->left)
            {
                node *aux = root->right;
                delete root;
                count--;
                return aux;
            }

            if (!root->right)
            {
                node *aux = root->left;
                delete root;
                count--;
                return aux;
            }

            // caso 3: dos hijos
            node *minDer = minNode(root->right);
            root->data = minDer->data;
            root->right = remove(root->right, minDer->data);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        root = balance(root);

        return root;
    }

    void printInOrder(node *root)
    {
        if (!root) return;
        printInOrder(root->left);
        std::cout << root->data << " ";
        printInOrder(root->right);
    }

public:
    avl()
    {
    }

    virtual void insert(T data) override
    {
        this->root = insert(this->root, data);
    }

    virtual void remove(T data) override
    {
        this->root = remove(this->root, data);
    }

    virtual void printInOrder() override
    {
        printInOrder(root);
    }

    virtual int size() override
    {
        return this->count;
    }

    virtual int height() override
    {
        return height(this->root);
    }
};