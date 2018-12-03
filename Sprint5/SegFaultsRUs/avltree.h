//Gabi Sanchez
#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>

using namespace std;

template <typename T>
class AVLTree
{
private:
    class AVLNode
    {
    public:
        string element; //changed to string
        AVLNode *left;
        AVLNode *right;
        int height;
        vector<string> docs;
        vector<int> freq;
        AVLNode(const string & theElement, AVLNode *It, AVLNode *rt, const string& d, int h = 0):element(theElement),left(It),right(rt),height(h){docs.push_back(d); freq.push_back(1);}

    };

    AVLNode *root;
    int size;
    int avgW;
    vector<string> words; //stores all of the words. used to get docs when writing persistant index.

public:
    AVLTree():root(nullptr){size = 0; avgW = 0;}
    AVLTree(const AVLTree& rhs):root(nullptr){*this = rhs;}

    /*
     * destructor that makes the tree empty
     */
    ~AVLTree()
    {
        makeEmpty();
    }

    /*
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const int & findMin() const
    {
//        if(isEmpty())
//            //throw UnderflowException();
        return findMin(root)->element;
    }

    /*
     * Find the largest item in the tree.
     * throw UnderflowException if empty
     */
    const int& findMax() const
    {
//        if(isEmpty())
//            throw UnderflowException();
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
        if(size == 0)
            return true;
        else
            return false;
    }

    /*
     * make the tree logically empty
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /*
     * insert x into the tree;
     * duplicates are ignored
     */
    void insert(const string& x, const string& d)
    {
        words.push_back(x);
        insert(x, root, d);
    }

    /*
     * returns the size of tree
     */
    int getSize()
    {
        return size;
    }

    bool search(const string& s)
    {
        search(s, root);
    }

    /*
     * adds document to tree to parse through
     */
    void addDoc(const string& s, const string& d)
    {
        addDoc(s, d, root);
    }

    /*
     * gets documents to parse through
     */
    vector<string> getD(const string& s)
    {
        return getD(s, root);
    }

    vector<int> getFreq(const string& s)
    {
        return getFreq(s,root);
    }

    vector<string> getDocs(const string& s)
    {
        return getDocs(s, root);
    }

    int getAVGW()
    {
        return avgW;
    }

    vector<string> getIndex()
    {
        vector<string> I;
        for(int i = 0; i < words.size(); i++)
        {
            vector<string> tempvec = getDocs(words[i]);
            string temp = words[i];
            for(int j = 0; j < tempvec.size(); j++)
            {
                temp += "|" + tempvec[j];
            }
            I.push_back(temp);
        }

        return I;

    }


    /*
     * clears the tree
     */
    void clearTree()
    {
        clearTree(root);
    }

private:

    /*
     * function that actually clears the tree
     * clearing from left node to right node and then fully deleting the node
     * also decreased size as nodes get deleted
     */
    void clearTree(AVLNode*& node)
    {
        if(node != NULL)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
            size--;
        }
        node = NULL;
    }

    /*
     * function that checks if document is there
     * and if it is gets the elements in the document
     * to save to a node that will be checked later
     */
    vector<string> getD(const string& s, AVLNode*& node)
    {
        vector<string> noResults;
        if(node == nullptr)
            return noResults;
        else if(s == node->element)
            return node->docs;
        else if(s < node->element)
            return getD(s, node->left);
        else if(s > node->element)
            return getD(s, node->right);
        else
            ;
    }

    vector<int> getFreq(const string& s, AVLNode*& node)
    {
        if(s == node->element)
            return node->freq;
        else if(s < node->element)
            return getFreq(s, node->left);
        else if(s > node->element)
            return getFreq(s, node->right);
        else
            ;
    }


    vector<string> getDocs(const string& s, AVLNode*& node)
    {
        if(s == node->element)
            return node->docs;
        else if(s < node->element)
            return getDocs(s, node->left);
        else if(s > node->element)
            return getDocs(s, node->right);
        else
            ;
    }



    /*
     * function that search there nodes for
     * a specific elemetn and returns that element
     */
    bool search(const string& s, AVLNode*& node)
    {
        if(node == nullptr)
            return false;
        else if(s < node->element)
            return search(s, node->left);
        else if(s > node->element)
            return search(s, node->right);
        else
            ;
    }

    void addDoc(const string& s, const string& d, AVLNode*& node)
    {
        if(s == node->element)
        {
            for(int i = 0; i < node->docs.size(); i++)
            {
                if(node->docs[i] == d)
                {
                    node->freq[i]++;
                    return;
                }
            }
            node->docs.push_back(d);
            node->freq.push_back(1);
            avgW++;
        }

        else if(s < node->element)
            return addDoc(s, d, node->left);
        else if(s > node->element)
            return addDoc(s, d, node->right);

    }


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
     * function that deletes the tree by
     * making it empty from left node to right node and then fully deleting the node
     */
    void makeEmpty(AVLNode*& t) const
    {
        if(t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

    /*
     * internal methodto insert into a subtree
     * x is the item to insert
     * t is the node that roots the subtree
     * set the new root of the subtree
     */
    void insert(const string& x, AVLNode*& t, const string& d)
    {
        if( t == nullptr)
        {
            t = new AVLNode(x, nullptr, nullptr,d);
            size ++;
            avgW++;
        }
        else if(x < t->element)
        {
            insert(x, t->left, d);
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
            insert(x, t->right, d);
            if(height(t->right) - height(t->left) == 2)
            {
                if(t->right->element < x)
                    rotateWithRightChild(t); //case #4
                else
                    doubleWithRightChild(t); //case #3
            }
        }
        else
        {
            addDoc(x,d);
        }

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
    void rotateWithRightChild(AVLNode*& k2)
    {
        AVLNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->right), height(k2->left)) + 1;
        k1->height = max(height(k1->right), k2->height) + 1;
        k2 = k1;
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
