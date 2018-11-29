#include "userinterface.h"

UserInterface::UserInterface(char *filepath)
{
    init(filepath);
}

void UserInterface::init(char * filepath)
{
    int indexType;
    cout << "Choose Index Type. (1 for AVLIndex, 2 for HashTableIndex)" << endl;
    cin >> indexType;
    if(indexType != 1 && indexType != 2)
    {
        cerr << "Invalid Entry." << endl;
        init(filepath);
    }

    IndexInterface * index;

    if(indexType == 1)
    {
        index = new avlindex;
    }
    else if(indexType == 2)
    {
        index = new htindex;
    }
    DocParser parse;
    parse.setDirectoryHead(filepath);
    parse.readFiles(index);


}
