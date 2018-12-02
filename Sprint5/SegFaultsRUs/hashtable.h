/*REID RUSSELL
 * Hash Table is responsible for creating a hash table, inserting the words and documents during parsing or read in from persistant index,
 * formatting the index and returning it in getIndex(), and handling and collisions that might occur.
 *
 * -Added Simple hash table implementation for ints.
 * -Fixed code to handle strings.
 * -Implemented stl hash function to convert strings to ints then set index by modding with total number of buckets.
 * -Added document tracking vector to HashNode.
 * -Added checkDocs to make sure repeat docs dont get added.
 * -Added displayHash for printing out populated indexes to see visual representation of the index.
 * -Added clear() to clear table.
 * -Added getIndex() to format and return the index for persisted index writing.
 * -Added search() for queries.
 * -Added freq vector to track frequency of word in each doc for ranking relavency
 * */
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
    vector<int> freq; //frequency of word in each doc
public:
    HashNode(string k, string doc);
    string getKey(){return key;}
    bool checkDocs(string doc); //should iterate through vector docs and return true if key already has that doc stored and false if not.
    void pushBack(string doc){docs.push_back(doc);}
    void pushBack(int i){freq.push_back(i);}
    bool isEmpty();
    void printDocs();
    vector<string> getDocs();
    void incFreq(string d);
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
    void clear();
    bool isEmpty();
    vector<string> search(vector<string> query);
    int getSize();
    vector<string> getIndex();

};



#endif // HASHTABLE_H
