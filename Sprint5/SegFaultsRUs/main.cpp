#include <iostream>
#include <string>
#include <dirent.h>
#include "docparser.h"
#include "avltree.h"
#include "hashtable.h"

//MEMORY MAPPING
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "userinterface.h"

//JSON PARSING
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

int main()
{
//    string a[] = {"hello","hello1","hello1","hello3","hello4","hello4"};
//    string b[] = {"11","12","13","14","15","16"};
//    int n = sizeof(a)/sizeof(a[0]);

//    HashTable h(500000);

//    for(int i = 0; i < n; i++)
//        h.insert(a[i],b[i]);

//    h.displayHash();
//    char* dir_path = argv[1];
//    string testWord = argv[2];

//    DocParser theDoc;
//    theDoc.setDirectoryHead(dir_path);
//    theDoc.readFiles();
//    cout << "Number of Files Processed: " << theDoc.getFP() << endl;

    UserInterface ui;
    ui.start();


    return 0;
}
