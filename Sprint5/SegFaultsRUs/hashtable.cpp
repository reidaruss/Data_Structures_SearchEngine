#include "hashtable.h"
//The link below is what I referenced for this hash table, however I have heavily modified it to handle strings and changed the container to a node
//https://www.geeksforgeeks.org/c-program-hashing-chaining/


HashTable::HashTable()
{

}

HashTable::HashTable(int v)
{
    this->bucket = v;
    table = new list<HashNode>[bucket];
    numWords = 0;
    avgW = 0;
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
    if(table[index].size() != 0)
    {
        list<HashNode>::iterator ci;
        for(ci = table[index].begin(); ci != table[index].end(); ci++)
        {
            if(ci->getKey() == x)
            {
                if(ci->checkDocs(d) == false)
                {
                    ci->pushBack(d);
                    ci->pushBack(1);
                    avgW++;
                    return;
                }
                if(ci->checkDocs(d) == true)
                {
                    ci->incFreq(d);
                }
                return;
            }
        }
        HashNode temp(x,d);
        table[index].push_back(temp);
        numWords++;
        avgW++;
    }
    else
    {
        HashNode temp(x,d);
        table[index].push_back(temp);
        numWords++;
        avgW++;
    }
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
                cout << " -> " << ci->getKey() << ": ";
                ci->printDocs();
            }
            cout << endl;
        }
    }
    cout << "Number of unique words = " << numWords << endl;
}

int HashTable::getnumWords()
{
    return numWords;
}

HashNode::HashNode(string k, string doc)
{
    key = k;
    docs.push_back(doc);
    freq.push_back(1);
}

bool HashNode::checkDocs(string doc) //should iterate through vector docs and return true if key already has that doc stored and false if not.
{
    for(int i = 0; i < docs.size(); i++)
    {
        if(doc == docs[i])
            return true;
    }
    return false;
}

bool HashNode::isEmpty()
{
    if(docs.size() == 0)
        return true;
    else
        return false;
}

void HashNode::printDocs()
{
    for(int i = 0; i < docs.size() - 1; i ++)
    {
        cout << docs[i] << "Freq: " << freq[i] << " -->";
    }
    cout << docs[docs.size()-1] << " Freq: " << freq[freq.size()-1];

}

vector<string> HashNode::getDocs()
{
    return docs;
}

void HashTable::clear()
{

    for(int i = 0; i < bucket; i++)
    {
        table[i].clear();
    }
    numWords = 0;
}

bool HashTable::isEmpty()
{
    if(numWords ==0)
        return true;
    else
        return false;
}

vector<string> HashTable::search(string query)
{
    vector<string> noResults;
    int index = hashFunction(query);
    if(table[index].size() != 0)
    {
        list<HashNode>::iterator ci;
        for(ci = table[index].begin(); ci != table[index].end(); ci++)
        {
            if(ci->getKey() == query)
            {
                return ci->docs;
            }
        }

    }
    else
    {
        return noResults;
    }
}

int HashTable::getSize()
{
    return numWords;
}

vector<string> HashTable::getIndex()
{
    vector<string> I;
    for(int i = 0; i < bucket; i++)
    {
        if(table[i].size() != 0)
        {
            list<HashNode>::iterator ci;
            for(ci = table[i].begin(); ci != table[i].end(); ci++)
            {
                string temp = ci->getKey();
                vector<string> tempvec= ci->getDocs();
                for(int j = 0; j < tempvec.size(); j++)
                {
                    temp += "|" + tempvec[j];
                }
                I.push_back(temp);
            }

        }
    }
    return I;
}

void HashNode::incFreq(string d)
{
    for(int i = 0; i < docs.size(); i ++)
    {
        if(d == docs[i])
        {
            freq[i]++;
        }
    }
}

vector<int> HashTable::getFreq(string query)
{
    int index = hashFunction(query);
    if(table[index].size() != 0)
    {
        list<HashNode>::iterator ci;
        for(ci = table[index].begin(); ci != table[index].end(); ci++)
        {
            if(ci->getKey() == query)
            {
                return ci->freq;
            }
        }

    }
}

