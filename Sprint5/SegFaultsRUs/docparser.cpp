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

//HTML INCLUDES


using namespace std;
using namespace rapidjson;

DocParser::DocParser(){
    filesProcessed = 0;
}

void DocParser::processData(){

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
            cout << dir->d_name << "|";
            parse(dir->d_name, index);
        }
    }

    closedir(directory);
}

void DocParser::parse(char* FILENAME, IndexInterface * index){

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

    //Format file
    Document d;
    d.Parse(map);
<<<<<<< HEAD
    Value& text = d["html_with_citations"];
    Value& title = d["local_path"];
=======
    Value& text = d["plain_text"];
    Value& html = d["html_with_citations"];
>>>>>>> 4f8817630bb7678f34630e76f2032c6836840bfa

    string temp = text.GetString();
    string temphtml = html.GetString();

    replaceSubStr(temp, "\n");
    replaceSubStr(temp, ".");
    replaceSubStr(temp, "(");
    replaceSubStr(temp, ")");
    replaceSubStr(temp, ",");
    replaceSubStr(temp, "]");
    replaceSubStr(temp, "[");
    replaceSubStr(temp, ";");
    replaceSubStr(temp, "-");
    replaceSubStr(temp, "*");
    replaceSubStr(temp, "</pre>");
    replaceSubStr(temp, "</span>");
    replaceSubStr(temp, "</a>");
    replaceSubStr(temp, "<pre class=\"inline\">");
    replaceSubStr(temp, "<span class=\"reporter\">");
    replaceSubStr(temp, "<span class=\"volume\">");
    replaceSubStr(temp, "<span class=\"page\">");
    replaceSubStr(temp, "<span class=\"citation no link\">");
    replaceSubStr(temp, "<span class=\"citation\" data id=\"");
    replaceSubStr(temp, "\"><a href=\"/");
    replaceSubStr(temp, "/\">");
    replaceSubStr(temp, "/");
    replaceSubStr(temp, "—");
    replaceSubStr(temp,"_");
    replaceSubStr(temp, "–");
    replaceSubStr(temp, "“");
    replaceSubStr(temp, "”");
    replaceSubStr(temp,"’");
    replaceSubStr(temp, "‘");
    replaceSubStr(temp,":");
    replaceSubStr(temp, "    ");

    //Add words to index
    string insertStr ="";
    istringstream str(temp);
    while(getline(str, insertStr, ' ')){
        size_t pos = insertStr.find(" ");
        string displayData = "File Name: " + str2 + "\nTitle: " + title.GetString() + "\n";
        if(pos == string::npos){
            index->insertI(insertStr, displayData);

            cout << insertStr << endl;
            index->insertI(insertStr, FILENAME);
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

