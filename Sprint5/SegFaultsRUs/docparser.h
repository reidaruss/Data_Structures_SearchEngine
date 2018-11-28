#ifndef DOCPARSER_H
#define DOCPARSER_H

#include <string>
#include <vector>

using namespace std;

class DocParser
{
public:
    DocParser();
    void processData();
    void readFiles();
    void parse(char* FILENAME);

    void setDirectoryHead(char* headToSet);

    void parseHTML(string s);
    int getFP();

private:
    char* directoryHead;
    int filesProcessed;

};



#endif // DOCPARSER_H
