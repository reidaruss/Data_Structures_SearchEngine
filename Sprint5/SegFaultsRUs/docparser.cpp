//MISC
#include <iostream>
#include <string>
#include <dirent.h>
#include "docparser.h"
#include "avltree.h"
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
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
#define RAPIDJSON_48BITPOINTER_OPTIMIZATION 0
//JSON PARSING
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

//HTML INCLUDES


using namespace std;
using namespace rapidjson;

DocParser::DocParser(){
    filesProcessed = 0;
}

void DocParser::processData(){

}
void DocParser::readFiles(){
    vector<string> v;
    v.push_back("95882.json");
    v.push_back("106440.json");
    v.push_back("145708.json");
    DIR *directory = opendir(directoryHead);
    struct dirent *dir;
    while(((dir = readdir(directory)) != NULL)){
        if((dir->d_type == 0x8)
            && (dir->d_name != v[0])
            && (dir->d_name != v[1])
            && (dir->d_name != v[2])){
            filesProcessed++;
            //cout << dir->d_name << "|";
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
    Value& text = d["plain_text"];
    //cout << '\t' << filesProcessed << '\t'  << endl;

//////////////////////////////////////////////
    //BELOW IS THE TEMPORARY SPECIAL CHARACTER REMOVAL AND INSERTION INTO AVLTREE USING GETLINE AND SPACE AS A DELIMITER
    StringBuffer buf;
    Writer<StringBuffer> writer(buf);
    d.Accept(writer);
    string temp = buf.GetString();
    //cout << temp << endl << endl << endl;


        temp.erase(remove(temp.begin(), temp.end(), '('), temp.end() ); //Reference I used to remove specific characters : https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string
        temp.erase(remove(temp.begin(), temp.end(), ')'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '['), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), ']'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '\''), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '\"'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '.'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '/'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), ','), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), ':'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '{'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '}'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '*'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), ';'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '-'), temp.end() );
        temp.erase(remove(temp.begin(), temp.end(), '_'), temp.end() );


    AVLTree<string> tree;
    string tempstr = "";
    istringstream str(temp);
    while(getline(str,tempstr, ' '))
    {
        tree.insert(tempstr);
    }

//ABOVE IS THE TEMPORARY SPECIAL CHARACTER REMOVAL AND INSERTION INTO AVLTREE USING GETLINE AND SPACE AS A DELIMITER
//////////////////////////////////////////////

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

int DocParser::getFP()
{
    return filesProcessed;
}

