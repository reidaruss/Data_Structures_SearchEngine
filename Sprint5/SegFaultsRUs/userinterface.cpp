#include "userinterface.h"

UserInterface::UserInterface(char *file)
{
    filesParsed = 0;
    filepath = file;
    start();
}

void UserInterface::start()
{
    int choice = 0;
    cout << "Welcome to SCOTUS Opinion Search Engine." << endl;
    cout << "Please enter 1 for maintenance mode or 2 for interactive mode." << endl;
    cin >> choice;
    if(choice == 1)
        maintenance();
    else if(choice == 2)
        init();
    else
    {
        cerr << "Invalid entry." << endl;
        start();
    }


}

void UserInterface::maintenance()
{
    string uIn = "";
    cout << "___________________________________________" << endl;
    cout << "               MAINTENANCE MENU" << endl;
    cout << "___________________________________________" << endl;
    cout << "OPTION: | Exit | Add Opinion | Clear Index |" << endl;
    cout << "COMMAND:| exit |    ao       |     ci      |" <<endl;
    cout << "________|______|_____________|_____________|" << endl << endl;
    cin >> uIn;
    transform(uIn.begin(), uIn.end(), uIn.begin(), ::tolower);
    if(uIn == "exit")
    {
        return;
    }
    else
    {
        cerr << "Invalid Entry." << endl;
        maintenance();
    }
}

void UserInterface::init()
{
    int indexType;
    cout << "Choose Index Type. (1 for AVLIndex, 2 for HashTableIndex)" << endl;
    cin >> indexType;
    if(indexType != 1 && indexType != 2)
    {
        cerr << "Invalid Entry." << endl;
        init();
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
    string uIn = ""; //user input
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
