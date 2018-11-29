#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "indexinterface.h"
#include "avltree.h"
#include "docparser.h"
#include "queryprocessor.h"
#include "avlindex.h"
#include "htindex.h"
#include <algorithm>

class UserInterface
{
private:
    int filesParsed;
    IndexInterface * index;
public:
    UserInterface(char * filepath);
    void init(char *filepath);
    void menu();
};

#endif // USERINTERFACE_H
