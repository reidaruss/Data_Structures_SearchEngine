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
    vector<string> searchIndex(vector<string> query);
    void insertI(string s, string d);
    void displayI();
    int getUWords();
    bool isEmpty();
    void clearIndex();
};

#endif // HTINDEX_H
