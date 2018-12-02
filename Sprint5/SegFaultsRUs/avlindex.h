//Reid Russell
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
    vector<string> searchIndex(vector<string> query);
    //void searchIndex(vector<string> query);
    void displayI();
    int getUWords();
    bool isEmpty();

};

#endif // AVLINDEX_H
