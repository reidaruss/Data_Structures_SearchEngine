#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "indexinterface.h"
#include "avltree.h"
#include "docparser.h"
#include "queryprocessor.h"
#include "avlindex.h"
#include "htindex.h"

class UserInterface
{
public:
    UserInterface(char * filepath);
    void init(char *filepath);

};

#endif // USERINTERFACE_H
