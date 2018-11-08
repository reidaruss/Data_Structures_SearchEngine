#ifndef AVLTREE_H
#define AVLTREE_H
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

    ~AvlTree(){makeEmpty();}

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



};


#endif // AVLTREE_H
