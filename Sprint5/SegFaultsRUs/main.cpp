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

    UserInterface ui; //Initializes the user interface.
    ui.start();       //Starts the program.


    return 0;
}
