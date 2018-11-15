#ifndef DOCPARSER_H
#define DOCPARSER_H

#include <string>

using namespace std;

class DocParser
{
public:
    DocParser();
    void processData();
    void readFiles();
    void parse(char* FILENAME);

    void setDirectoryHead(char* headToSet);
private:
    char* directoryHead;
    int filesProcessed;

};



#endif // DOCPARSER_H
