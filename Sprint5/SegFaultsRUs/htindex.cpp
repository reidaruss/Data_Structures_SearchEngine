#include "htindex.h"


/*This constructor initializes the hash table
 * and sets the number of buckets to a large
 * prime number to avoid collisions.
 */
htindex::htindex()
{
    ht = new HashTable(15485867); //big prime number to reduce collissions
}

vector<string> htindex::searchIndex(string query)
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

vector<int> htindex::getFreq(string query)
{
    return ht->getFreq(query);
}

int htindex::getAVGW()
{
    return ht->getAVGW();
}
