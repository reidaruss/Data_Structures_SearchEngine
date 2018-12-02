//Reid Russell
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <string>
#include <vector>

using namespace std;

class IndexInterface
{
public:
    IndexInterface();
    virtual vector<string> searchIndex(vector<string> query) = 0;
    virtual void insertI(string s, string d) = 0;
    virtual void displayI() =0;
    virtual int getUWords() =0;
    virtual bool isEmpty() = 0;
    virtual void clearIndex() =0;

};

#endif // INDEXINTERFACE_H
