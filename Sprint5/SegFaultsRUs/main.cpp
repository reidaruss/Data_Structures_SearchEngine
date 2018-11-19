#include <iostream>
#include <string>
#include <dirent.h>
#include "docparser.h"
#include "avltree.h"

//MEMORY MAPPING
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

//JSON PARSING
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

int main(int argc, char *argv[])
{
    char* dir_path = argv[1];
    string testWord = argv[2];

    DocParser theDoc;
    theDoc.setDirectoryHead(dir_path);
    theDoc.readFiles();
    cout << "Number of Files Processed: " << theDoc.getFP() << endl;

    return 0;
}
