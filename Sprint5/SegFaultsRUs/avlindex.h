#ifndef AVLINDEX_H
#define AVLINDEX_H
#include "indexinterface.h"
#include "avltree.h"

class avlindex : public IndexInterface
{
private:
    AVLTree<string> tree;
public:
    avlindex();
    void insertI(string s, string d);
    void searchIndex(string s);
    void displayI();

};

#endif // AVLINDEX_H
