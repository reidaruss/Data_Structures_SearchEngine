#ifndef AVLINDEX_H
#define AVLINDEX_H
#include "indexinterface.h"
#include "avltree.h"

class avlindex : public IndexInterface
{
private:
    AVLTree<string> avlI;
public:
    avlindex();
    void createIndex();
    void searchIndex(string s);

};

#endif // AVLINDEX_H
