//REID RUSSELL
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <list>
#include <vector>
#include <functional>


using namespace std;

class HashNode
{
    friend class HashTable;
private:
    string key;
    vector<string> docs;
public:
    HashNode(string k, string doc)
    {
        key = k;
        docs.push_back(doc);
    }
    string getKey(){return key;}
    bool checkDocs(string doc) //should iterate through vector docs and return true if key already has that doc stored and false if not.
    {
        for(int i = 0; i < docs.size(); i++)
        {
            if(doc == docs[i])
                return true;
        }
        return false;
    }
    void pushBack(string doc){docs.push_back(doc);}
    bool isEmpty()
    {
        if(docs.size() == 0)
            return true;
        else
            return false;
    }

    void printDocs()
    {
        for(int i = 0; i < docs.size() - 1; i ++)
            cout << docs[i] << " -->";
        cout << docs[docs.size()-1];

    }

};

class HashTable
{
private:

    int bucket; //Number of buckets
    list<HashNode> *table; //pointer to an array containing buckets
    int numWords; //number of unique words;
public:
    HashTable();
    HashTable(int v);
    void insert(string x, string d); //insert
    void remove(string key);   //removes a key from hash table
    int hashFunction(const string &x); //hash function to map values to key
    void displayHash();
    int getnumWords();
};



#endif // HASHTABLE_H
