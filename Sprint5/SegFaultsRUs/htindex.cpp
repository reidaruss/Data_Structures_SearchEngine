#include "htindex.h"



htindex::htindex()
{
    ht = new HashTable(500000);
}

void htindex::searchIndex(string s)
{

}

void htindex::insertI(string s, string d)
{
    ht->insert(s,d);
}
