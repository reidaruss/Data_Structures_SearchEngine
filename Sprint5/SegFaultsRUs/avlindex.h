/*REID RUSSELL
 * AVLIndex acts as the link between the Index Interface abstract class and the actual avl tree. It is responsible
 * for receiving general function calls from the Index Interface and calling the right functions for avl tree.
 *
 *
 * -Added insertI for populating index.
 * -Added getUwords for getting the number of nodes (unique words) in the index.
 * -Added isEmpty() for checking if clearIndex() has successfuly cleared the index.
 * -Added clearIndex for clearing Index.
 * -Added search index for queries.
 * -Added getSize().
 * -Added getIndex() for Persisted Index formatting and creation.
 * */
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
    void displayI();
    int getUWords();
    bool isEmpty();
    void clearIndex();
    int getSize();
    vector<string> getIndex();


};

#endif // AVLINDEX_H
