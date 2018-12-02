#include "persistedindex.h"

PersistedIndex::PersistedIndex()
{

}

PersistedIndex::PersistedIndex(IndexInterface *index)
{
    pindex = index;
}

void PersistedIndex::writeIndex()
{
    vector<string> I = pindex->getIndex();
    ofstream file("index.txt");
    if(file.is_open())
    {
        for(int i = 0; i < I.size(); i++)
        {
            file << I[i] << endl;
        }
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

void PersistedIndex::readIndex()
{

}
