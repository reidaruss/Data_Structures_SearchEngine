#include "userinterface.h"

UserInterface::UserInterface(char *filepath)
{
    init(filepath);
    filesParsed = 0;

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
    filesParsed = parse.getFP();

    menu();

}

void UserInterface::menu()
{
    string uIn; //user input
    cout << "________________________________________________________" << endl;
    cout << "                           MENU" << endl;
    cout << "________________________________________________________" << endl;
    cout << "OPTION: | Exit | Display Index | Number of Files Parsed |" << endl;
    cout << "COMMAND:| exit |    dindex     |         files          |" <<endl;
    cout << "________|______|_______________|________________________|" << endl << endl;
    cin >> uIn;
    transform(uIn.begin(), uIn.end(), uIn.begin(), ::tolower);

    if(uIn == "dindex")
    {
        index->displayI();
        menu();

    }
    else if(uIn == "files")
    {

        cout << "Number of files parsed: " << filesParsed << endl;
        menu();
    }
    else if(uIn == "exit")
        return;
    else
    {
        cerr << "Invalid Entry." << endl;
        menu();
    }

}

//make numfiles parsed data member in ui
//make index a data member so dont have to keep passing it
