#include <iostream>
#include <string>
#include <dirent.h>
#include "docparser.h"

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
    DocParser theDoc;
    theDoc.setDirectoryHead("/home/student/Desktop/testJSONFiles/");
    theDoc.readFiles();

    return 0;
}
