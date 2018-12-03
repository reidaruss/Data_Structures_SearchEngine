//Alex
#ifndef DOCPARSER_H
#define DOCPARSER_H
#include "hashtable.h"
#include <string>
#include <vector>
#include "indexinterface.h"

using namespace std;

class DocParser
{
public:
    DocParser();
    void processData();
    void readFiles(IndexInterface * index);
    void parse(char* FILENAME, IndexInterface * index);

    void setDirectoryHead(char* headToSet);
    void replaceSubStr(string &main, const string &toErase);
    string getFileExcerpt(string FILENAME);

    void parseHTML(string s);
    int getFP();

private:
    char* directoryHead;
    int filesProcessed;
};



#endif // DOCPARSER_H
