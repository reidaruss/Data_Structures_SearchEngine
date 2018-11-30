//Reid Russell
#ifndef HTINDEX_H
#define HTINDEX_H
#include "indexinterface.h"
#include "hashtable.h"

using namespace std;

class htindex : public IndexInterface
{
private:
    HashTable * ht;
public:
    htindex();
    void searchIndex(string s);
    void insertI(string s, string d);
    void displayI();
    int getUWords();
};

#endif // HTINDEX_H
