#ifndef DOCPARSER_H
#define DOCPARSER_H
#import "avltree.h"

class DocParser
{
public:
    DocParser();
    AVLTree input();
    void JSONParse();
};

#endif // DOCPARSER_H
