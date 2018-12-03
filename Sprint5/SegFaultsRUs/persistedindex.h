/*REID RUSSELL
 * The Persisted Index is called upon the exit command from the user in UI.
 * When called it takes in the index and calles a getIndex() function that formats the index
 * in a manner that can be written to a file and easily read back in and inserted into another index.
 *
 * -Added writeIndex() and readIndex()
 * -Added getIndex() in hashTable and AVLTree to format each word and vector of docs in a way that can be read in easily.
 * -Added writing when exit is used in UI
 * -Added reading when program starts
 * */
#ifndef PERSISTEDINDEX_H
#define PERSISTEDINDEX_H
#include <stdio.h>
#include <string>
#include "indexinterface.h"
#include <fstream>
#include <iostream>
#include "avlindex.h"
#include "htindex.h"
#include <sstream>

using namespace std;

class PersistedIndex
{
private:
    IndexInterface* pindex;
    int indexType;

public:
    PersistedIndex();
    PersistedIndex(IndexInterface* index);
    void writeIndex(int indexType, int numWords);
    IndexInterface *readIndex();
    int getIndexType(){return indexType;}
};

#endif // PERSISTEDINDEX_H
