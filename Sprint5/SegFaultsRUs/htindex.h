/*REID RUSSELL
 * Hash Table Index is responsible for being the link between the Index Interface abstract class and
 * the hash table. It takes the general functions from the Index Interface and calls the right functions from HashTable
 * and returns the results (if not void).
 *
 * -Added displayI() to display the index (hashtable only).
 * -Added insertI for populating index.
 * -Added getUwords for getting the number of nodes (unique words) in the index.
 * -Added isEmpty() for checking if clearIndex() has successfuly cleared the index.
 * -Added clearIndex for clearing Index.
 * -Added search index for queries.
 * -Added getSize().
 * -Added getIndex() for Persisted Index formatting and creation.
 *
 * */
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
    int getSize();
    vector<string> getIndex();
    vector<int> getFreq(vector<string> query);

};

#endif // HTINDEX_H
