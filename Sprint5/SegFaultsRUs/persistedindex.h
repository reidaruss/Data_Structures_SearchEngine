#ifndef PERSISTEDINDEX_H
#define PERSISTEDINDEX_H
#include <stdio.h>
#include <string>
#include "indexinterface.h"
#include <fstream>
#include <iostream>

using namespace std;

class PersistedIndex
{
private:
    IndexInterface* pindex;

public:
    PersistedIndex();
    PersistedIndex(IndexInterface* index);
    void writeIndex();
    void readIndex();
};

#endif // PERSISTEDINDEX_H
