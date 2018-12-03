//MISC
#include <iostream>
#include <algorithm>
#include <functional>
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
//STEMMER INCLUDES
#include "english_stem.h"


using namespace std;
using namespace rapidjson;

DocParser::DocParser(){
    filesProcessed = 0;

}

void DocParser::readFiles(IndexInterface * index){
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
            parse(dir->d_name, index);
        }
    }
    closedir(directory);
}

void DocParser::parse(char* FILENAME, IndexInterface * index){
    vector<string> parsingStrings = {"\n",".","(",")",",","]","[",";","-","*","</pre>","</span>","</a>",
                                     "<pre class=\"inline\">","<span class=\"reporter\">","<span class=\"volume\">",
                                    "<span class=\"page\">","<span class=\"citation no link\">",
                                    "<span class=\"citation\" data id=\"","\"><a href=\"/","/\">","/","—","_","–","“","”",
                                    "’","‘",":","    "};
    string str1 = directoryHead;
    string str2 = FILENAME;
    string path = str1+str2;
    const char* FILEPATH = path.c_str();
    struct stat buffer;
    int status, fd;
    char *map;
    //Find # of characters in file & set file size
    fd = open(FILEPATH, O_RDONLY);
    status = fstat(fd, &buffer);
    const int FILESIZE = buffer.st_size;
    //Memory map the file
    if (fd == -1){

        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    //Extract data from file
    Document d;
    d.Parse(map);
    Value& text = d["html_with_citations"];
    Value& tempTitle = d["absolute_url"];
    string temp = text.GetString();
    string title = tempTitle.GetString();
    //Parse file
    replaceSubStrings(temp, parsingStrings);
    //removeStopWords(temp);

    //Add words to index
    string insertStr ="";
    istringstream str(temp);
    while(getline(str, insertStr, ' ')){
        size_t pos = insertStr.find(" ");
        string displayData = "File Name: " + str2 + "\tTitle: " + title;
        if(pos == string::npos){
            index->insertI(insertStr, displayData);

        }
    }

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

void DocParser::removeStopWords(string &main){

    string path = "../SegFaultsRUs/externalFileDependencies/stopWords.txt";
    //Load stop word file
    const char* FILEPATH = path.c_str();
    struct stat buffer;
    int status, fd;
    char *map;
    //Find # of characters in file & set file size
    fd = open(FILEPATH, O_RDONLY);
    status = fstat(fd, &buffer);
    const int FILESIZE = buffer.st_size;
    //Memory map the file
    if (fd == -1){
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    //Load stop words into vector
    string importedList = map;
    istringstream str(importedList);
    vector<string> stopWordList;
    string tempString = "";
    while(getline(str, tempString, '\n')){
        stopWordList.push_back(" "+tempString+" ");
    }
    //Convert main opinion string to lowercase
    transform(main.begin(), main.end(), main.begin(), ::tolower);
    //Remove stop words
    replaceSubStrings(main, stopWordList);

}

void DocParser::setDirectoryHead(char* headToSet){
    directoryHead = headToSet;
}

int DocParser::getFP()
{
    return filesProcessed;
}

void DocParser::replaceSubStr(string &main, const string &toErase){
    size_t pos = string::npos;
    while((pos = main.find(toErase)) != string::npos){
        main.replace(pos, toErase.length(), " ");
    }
}

void DocParser::replaceSubStrings(string &main, const vector<string> &v){
    for(int i = 0; i < v.size(); i++){
        replaceSubStr(main, v[i]);
    }
}

void DocParser::stemInput(string &main){
}

string DocParser::stemSearch(string &s){

}

string DocParser::getFileExcerpt(string FILENAME){
        vector<string> parsingStrings = {"\n",".","(",")",",","]","[",";","-","*","</pre>","</span>","</a>",
                                     "<pre class=\"inline\">","<span class=\"reporter\">","<span class=\"volume\">",
                                    "<span class=\"page\">","<span class=\"citation no link\">",
                                    "<span class=\"citation\" data id=\"","\"><a href=\"/","/\">","/","—","_","–","“","”",
                                    "’","‘",":","    "};
        string dhead = directoryHead;
        string path = dhead + FILENAME;
        const char* FILEPATH = path.c_str();
        struct stat buffer;
        int status, fd;
        char *map;
        //Find # of characters in file & set file size
        fd = open(FILEPATH, O_RDONLY);
        status = fstat(fd, &buffer);
        const int FILESIZE = buffer.st_size;

        //Memory map the file
        if (fd == -1){
            perror("Error opening file for reading");
            exit(EXIT_FAILURE);
        }
        map = (char*)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);

        //Format file
        Document d;
        d.Parse(map);

        Value& text = d["html_with_citations"];
        string temp = text.GetString();
        replaceSubStrings(temp, parsingStrings);

        //Format excerpt
        string outputString = "";
        string insertStr ="";
        istringstream str(temp);
        for (int i = 0; i < 300; i++){
            getline(str, insertStr, ' ');
            outputString.append(insertStr + " ");
        }

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

        return outputString;
    }

