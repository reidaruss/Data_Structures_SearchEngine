//MISC
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
//JSON PARSING OPTIMIZATION
#if defined(__SSE4_2__)
    #define RAPIDJSON_SSE42
#elif defined(__SSE2__)
    #define RAPIDJSON_SSE2
#elif defined(__ARM_NEON)
    #define RAPIDJSON_NEON
#endif
//JSON PARSING
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

DocParser::DocParser(){
    filesProcessed = 0;
}

void DocParser::processData(){

}
void DocParser::readFiles(){
    DIR *directory = opendir(directoryHead);
    struct dirent *dir;
    while(((dir = readdir(directory)) != NULL)){
        if(dir->d_type == 0x8){
            filesProcessed++;
            //cout << dir->d_name;
            parse(dir->d_name);
        }
    }
    closedir(directory);
}

void DocParser::parse(char* FILENAME){
    string str1 = directoryHead;
    string str2 = FILENAME;
    string path = str1+str2;

    const char* FILEPATH = path.c_str();
    struct stat buffer;
    int status, fd, i;
    char *map;
    //Find # of characters in file & set file size
    fd = open(FILEPATH, O_RDONLY);
    status = fstat(fd, &buffer);
    const int NUMCHAR = buffer.st_size/sizeof(char);
    const int FILESIZE = buffer.st_size;

    //Memory map the file
    if (fd == -1){
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);

    //Test access to mapped file
    Document d;
    d.Parse(map);
    Value& sha = d["sha1"];
    //cout << '\t' << filesProcessed << '\t' << sha.GetString() << endl;

    //Un-memory map the file
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    if (munmap(map, FILESIZE) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fd);
}

void DocParser::setDirectoryHead(char* headToSet){
    directoryHead = headToSet;
}

