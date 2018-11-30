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
    cout << "____________________________________________" << endl;
    cout << "|              MAINTENANCE MENU            |" << endl;
    cout << "|__________________________________________|" << endl;
    cout << "|OPTION: | Exit | Add Opinion | Clear Index|" << endl;
    cout << "|--------|------|-------------|------------|" << endl;
    cout << "|COMMAND:| exit |    ao       |     ci     |" << endl;
    cout << "|------------------------------------------|" << endl;
    cout << "|DESCRIPTION: Add -d to a command to get a |" << endl;
    cout << "|description of that command. (ex: ao-d)   |" << endl;
    cout << "|__________________________________________|" << endl << endl;
    cin >> uIn;
    transform(uIn.begin(), uIn.end(), uIn.begin(), ::tolower);
    if(uIn == "exit")
    {
        return;
    }
    else if(uIn == "exit-d")
    {
        cout << "exit: Closes the program." << endl;
        maintenance();
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
    cout << "_________________________________________________________" << endl;
    cout << "|                  INTERACTIVE MENU                     |" << endl;
    cout << "|_______________________________________________________|" << endl;
    cout << "|OPTION: | Exit | Display Index | Number of Files Parsed|" << endl;
    cout << "|--------|------|---------------|-----------------------|" << endl;
    cout << "|COMMAND:| exit |    dindex     |         stats         |" << endl;
    cout << "|-------------------------------------------------------|" << endl;
    cout << "|DESCRIPTION: Add -d to a command to get a description  |" << endl;
    cout << "|             of that command. (ex: stats-d)            |" << endl;
    cout << "|_______________________________________________________|" << endl << endl;
    cin >> uIn;
    transform(uIn.begin(), uIn.end(), uIn.begin(), ::tolower);

    if(uIn == "dindex")
    {
        index->displayI();
        menu();

    }
    else if(uIn == "stats")
    {

        cout << "Number of files parsed: " << filesParsed << endl;
        cout << "Number of unique words: " << index->getUWords() << endl;
        menu();
    }
    else if(uIn == "exit")
        return;
    else if(uIn == "dindex-d")
    {
        cout << "dindex: Displays the Index." << endl;
        menu();
    }
    else if(uIn == "stats-d")
    {
        cout << "stats: Displays the statistics of the search engine." << endl;
        menu();
    }
    else if(uIn == "exit-d")
    {
        cout << "exit: Closes the program." << endl;
        menu();
    }
    else
    {
        cerr << "Invalid Entry." << endl;
        menu();
    }

}
