#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;

template <typename T>
class AVLTree
{
private:
    class AVLNode
    {
    public:
        int element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode(const int & theElement, AVLNode *It, AVLNode *rt, int h = 0):element(theElement),left(It),right(rt),height(h){}
    };

    AVLNode *root;

public:
    AVLTree():root(nullptr){}
    AVLTree(const AVLTree& rhs):root(nullptr){*this = rhs;}

    ~AvlTree()
    {
        makeEmpty();
    }

    /*
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const int & findMin() const
    {
        if(isEmpty())
            throw UnderflowException();
        return findMin(root)->element;
    }

    /*
     * Find the largest item in the tree.
     * throw UnderflowException if empty
     */
    const int& findMax() const
    {
        if(isEmpty())
            throw UnderflowException();
        return findMax(root)->element;
    }

    /*
     * returns true if x is found in the tree
     */
    bool contains(const int& x) const
    {
        return contains(x, root);
    }

    /*
     * test if the tree is logically empty
     * return true if empty, false otherwise
     */
    bool isEmpty() const
    {
        return root == NULL;
    }

    /*
     * make the tree logically emoty
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /*
     * insert x into the tree;
     * duplicates are ignored
     */
    void insert(const int& x)
    {
        insert(x, root);
    }

private:

    /*
     * return the height of node t -1 if NULL
     */
    int height(AVLNode* t) const
    {
        return t == NULL ? - 1: t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs: rhs;
    }

    /*
     * internal methodto insert into a subtree
     * x is the item to insert
     * t is the node that roots the subtree
     * set the new root of the subtree
     */
    void insert(const int& x, AVLNode*& t)
    {
        if( t == nullptr)
            t = new AVLNode(x, nullptr, nullptr);
        else if(x < t->element)
        {
            insert(x, t->left);
            if(height(t->left)-height(t->right) == 2)
            {
                if(x < t->left->element)
                    rotateWithLeftChild(t); //case#1
                else
                    doubleWithLeftChild(t); //case #2
            }
        }
        else if(t->element < x)
        {
            insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(t->right->element < x)
                    rotateWithRightChild(t); //case #4
                else
                    doubleWithRightChild(t); //case #3
            }
        }
        else; //no duplicates

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /*
     * rotate binary tree node with the left child
     * for AVL trees, this is a single rotation for case 1
     * update heights, then set new root
     */
    void rotateWithLeftChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /*
     * rotate binary tree node with the right child
     * for AVL trees, this is a single rotation for case 4
     * update heights, then set new root
     */
    void rotateWithRightChild(AVLNode*& k1)
    {
        AVLNode* k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), k1->height) + 1;
        k1 = k2;
    }

    /*
     * double rotate bonary tree node: first left child
     * with its right child; then node k3 with new left child
     * for AVL treees, this is a double rotation for case 2
     * update heights, then set new root
     */
    void doubleWithLeftChild(AVLNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /*
     * double rotate bonary tree node: first right child
     * with its right child; then node k1 with new right child
     * for AVL treees, this is a double rotation for case 3
     * update heights, then set new root
     */
    void doubleWithRightChild(AVLNode*& k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }


};


#endif // AVLTREE_H


//#endif // AVLTREE_H
