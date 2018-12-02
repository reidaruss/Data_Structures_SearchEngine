#include "htindex.h"



htindex::htindex()
{
    ht = new HashTable(500000);
}

vector<string> htindex::searchIndex(vector<string> query)
{
    return ht->search(query);
}

void htindex::insertI(string s, string d)
{
    ht->insert(s,d);
}

void htindex::displayI()
{
    ht->displayHash();
}

int htindex::getUWords()
{
    return ht->getnumWords();
}

bool htindex::isEmpty()
{
    return ht->isEmpty();
}

void htindex::clearIndex()
{
    ht->clear();
}

int htindex::getSize()
{
    return ht->getSize();
}

vector<string> htindex::getIndex()
{
    return ht->getIndex();
}

vector<int> htindex::getFreq(vector<string> query)
{
    return ht->getFreq(query);
}
