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
    void createIndex();
    void searchIndex(string s);
};

#endif // HTINDEX_H
