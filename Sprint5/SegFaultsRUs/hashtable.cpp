#include "hashtable.h"
//The link below is what I referenced for this hash table, however I have heavily modified it to handle strings and changed the container to a node
//https://www.geeksforgeeks.org/c-program-hashing-chaining/


HashTable::HashTable()
{

}

/*Constructor that sets the initial values.
 * This is called in htIndex and bucket
 * is specified there.
 * */
HashTable::HashTable(int v)
{
    this->bucket = v;
    table = new list<HashNode>[bucket];
    numWords = 0;
    avgW = 0;
}

/*This function takes a word(string) and uses the
 * STL hash function to convert it to an int
 * and then modded with that number of buckets
 * to ensure the word is not hashed out of bounds.
 * */
int HashTable::hashFunction(const string& x)
{
    hash<string> hash_fn;
    size_t hash = hash_fn(x);
    hash %= bucket;
    return hash;
}

/*The insert function takes string x(word) and d(document)
 * hashes the word, navigates to the index and looks to see if
 * the word is already at that index. If it is not it creates a new
 * node and pushes it back at that index. If it does find the word already
 * there it checks to see if the document is already in the vector
 * of docs. If it is it increments the frequency counter at the same index.
 * If it is not it pushes back a new document to the docs vector.
 * */
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

/*This function is called when dindex is entered into the
 * Interactive menu in UI. It iterates through the entire
 * hash table and prints all of the nodes that are populated.
 * Used for visual representation of the index.
 */
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

