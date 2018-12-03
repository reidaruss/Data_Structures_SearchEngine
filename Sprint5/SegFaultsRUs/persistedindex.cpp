#include "persistedindex.h"

PersistedIndex::PersistedIndex()
{

}

PersistedIndex::PersistedIndex(IndexInterface *index)
{
    pindex = index;
}

void PersistedIndex::writeIndex(int indexType, int numWords)
{
    if(numWords == 0)
    {
        ofstream file("index.txt");
        if(file.is_open())
        {
            file << indexType << '\n';
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }
    else
    {
        vector<string> I = pindex->getIndex();
        ofstream file("index.txt");
        if(file.is_open())
        {
            file << indexType << '\n';
            for(int i = 0; i < I.size(); i++)
            {
                file << I[i] << '\n';
            }
        }
        else
        {
            cout << "Unable to open file." << endl;
        }
    }

}

IndexInterface* PersistedIndex::readIndex()
{

    string tempstr = "";
    ifstream file("index.txt");

    if(file.is_open())
    {
        file >> indexType;
        getline(file, tempstr);
        if(indexType == 0)
        {
            return NULL;
        }
        else if(indexType == 1)
            pindex = new avlindex;
        else if(indexType == 2)
            pindex = new htindex;
        else
            return NULL;
        while(getline(file, tempstr, '\n'))
        {
            vector<string> node;
            istringstream ss(tempstr);
            string s;
            while(getline(ss,s, ' '))
            {
                node.push_back(s);
            }
            pindex->insertI(node[0],node[1]);
            for(int i = 2; i < node.size(); i++)
            {
                pindex->insertI(node[0],node[i]);
            }
        }
        file.close();
    }
    else
        return NULL;

    return pindex;


}

