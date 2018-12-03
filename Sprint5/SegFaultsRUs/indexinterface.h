/*REID RUSSELL
 * IndexInterface is an abstract class integral to the inverted file index data structure.
 * It takes care of calling the right functions for hash table index and avl tree index based on the existing index.
 *
 * -Added displayI() to display the index (hashtable only).
 * -Added insertI for populating index.
 * -Added getUwords for getting the number of nodes (unique words) in the index.
 * -Added isEmpty() for checking if clearIndex() has successfuly cleared the index.
 * -Added clearIndex for clearing Index.
 * -Added search index for queries.
 * -Added getSize().
 * -Added getIndex() for Persisted Index formatting and creation.
 * */
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include <vector>

using namespace std;

class IndexInterface
{
public:
    IndexInterface();
    virtual vector<string> searchIndex(string query) = 0;
    virtual void insertI(string s, string d) = 0;
    virtual void displayI()   =0;
    virtual int getUWords()   =0;
    virtual bool isEmpty()    =0;
    virtual void clearIndex() =0;
    virtual int getSize()     =0;
    virtual vector<string> getIndex() = 0;
    virtual vector<int> getFreq(string query) = 0;
    virtual int getAVGW() = 0;


};

#endif // INDEXINTERFACE_H
