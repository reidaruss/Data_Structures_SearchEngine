//REID RUSSELL
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "indexinterface.h"
#include "avltree.h"
#include "docparser.h"
#include "queryprocessor.h"
#include "avlindex.h"
#include "htindex.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <stdio.h>
#include "queryprocessor.h"

class UserInterface
{
private:
    int filesParsed;
    IndexInterface * index;
    char * filepath;
    int indexType;
public:
    UserInterface();
    void start();
    void maintenance();
    void init();
    void menu();
};

#endif // USERINTERFACE_H
