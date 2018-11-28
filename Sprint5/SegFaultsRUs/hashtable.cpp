#include "hashtable.h"

HashTable::HashTable(int v)
{
    this->bucket = v;
    table = new list<HashNode>[bucket];
}

int HashTable::hashFunction(const string& x)
{
    hash<string> hash_fn;
    size_t hash = hash_fn(x);
    hash %= bucket;
    return hash;
}

void HashTable::insert(string x, string d)  //x is the key, d is the doc. need to add a doc string var in parser to keep track of when doc changes
{
    int index = hashFunction(x);
    list<HashNode>::iterator ci;
    for(ci = table[index].begin(); ci != table[index].end(); ci++)
    {
        if(ci->getKey() == x)
        {
            if(ci->checkDocs(d) == false)
            {
                ci->pushBack(d);
                break;
            }
            return;
        }
    }
    HashNode temp(x,d);
    table[index].push_back(temp);
}

//void HashTable::remove(string key)
//{
//    int index = hashFunction(key); //get the hash index of key
//    list<string> :: iterator i;    //find the key in the list
//    for(i = table[index].begin(); i != table[index].end(); i++)
//    {
//        if(*i == key)
//            break;
//    }
//    if(i != table[index].end())
//        table[index].erase(i);
//}

void HashTable::displayHash()
{
    for(int i = 0; i < bucket; i++)
    {
        if(table[i].size() != 0)
        {

            cout << i;
            list<HashNode>::iterator ci;
            for(ci = table[i].begin(); ci != table[i].end(); ci++)
            {
                cout << " --> " << ci->getKey();
            }
            cout << endl;
        }

    }
}


