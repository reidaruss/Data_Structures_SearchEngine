//Reid Russell
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>

using namespace std;

class IndexInterface
{
public:
    IndexInterface();
    virtual void searchIndex(string s) = 0;
    virtual void insertI(string s, string d) = 0;
    virtual void displayI() =0;
    virtual int getUWords() =0;
    virtual bool isEmpty() = 0;

};

#endif // INDEXINTERFACE_H
