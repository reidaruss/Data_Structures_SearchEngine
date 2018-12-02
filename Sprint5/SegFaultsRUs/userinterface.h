/*REID RUSSELL
 * This class is the front end of the search engine. Based on user input the user can add files, choose index type, clear the index,
 * show statistics about the index, perform a search query, print the index (hash table only), and switch between menus.
 * All backend is called from this class so objects associated with other classes are instantiated and used here.
 * The Persisted Index is written to file upon exiting the program.
 *
 * -Added Simple UI
 * -Added option to add files
 * -Added option to clear index
 * -Added switching between menus
 * -Added descriptions of each command
 * -Removed displayIndex from menu but kept the option to use (hash table only)
 * -Added writing persisted Index to file upon exit
 *
 * */
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
#include "persistedindex.h"


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
