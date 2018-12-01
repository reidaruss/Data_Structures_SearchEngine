#include "userinterface.h"

UserInterface::UserInterface()
{
    filesParsed = 0;
    indexType = 0;
    cout << "Welcome to SCOTUS Opinion Search Engine." << endl;
}

void UserInterface::start()
{
    int choice = 0;
    cout << "Please enter 1 for maintenance mode or 2 for interactive mode." << endl;
    cin >> choice;
    if(choice == 1)
        maintenance();
    else if(choice == 2)
        menu();
    else
    {
        cerr << "Invalid entry." << endl;
        start();
    }


}

void UserInterface::maintenance()
{
    string uIn = "";
    cout << "_______________________________________________________________" << endl;
    cout << "|                         MAINTENANCE MENU                    |" << endl;
    cout << "|_____________________________________________________________|" << endl;
    cout << "|OPTION: | Exit | Interactive Menu | Add Opinion | Clear Index|" << endl;
    cout << "|--------|------|------------------|--------------------------|" << endl;
    cout << "|COMMAND:| exit |      int         |   ao        |     ci     |" << endl;
    cout << "|-------------------------------------------------------------|" << endl;
    cout << "|DESCRIPTION: Add -d to a command to get a                    |" << endl;
    cout << "|description of that command. (ex: ao-d)                      |" << endl;
    cout << "|_____________________________________________________________|" << endl << endl;
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
    else if(uIn == "int")
    {
        menu();
    }
    else if(uIn == "ci")
    {
        if(filesParsed == 0)
        {
            cout << "Index already empty. Please add opinions." << endl;
            maintenance();
        }
        else
        {
            //index->clear();
            if(filesParsed == 0)
            {
                cout << "Index Cleared." << endl;
                maintenance();
            }
            else
            {
                cerr << "Error Clearing Index.." << endl;
                maintenance();
            }

        }
    }
    else if(uIn == "ao")
    {
        string file;
        cout << "Please Enter A File Path: " ;
        cin >> file;
        if(filesParsed != 0)
        {
            delete filepath;
            filepath = new char[file.length() + 1];
            strcpy(filepath, file.c_str());
            init();
        }
        else
        {
            filepath = new char[file.length() + 1];
            strcpy(filepath, file.c_str());
            init();
        }

    }
    else
    {
        cerr << "Invalid Entry." << endl;
        maintenance();
    }
}

void UserInterface::init()
{
    if(indexType == 0)
    {
        cout << "Choose Index Type. (1 for AVLIndex, 2 for HashTableIndex)" << endl;
        cin >> indexType;
        if(indexType != 1 && indexType != 2)
        {
            cerr << "Invalid Entry." << endl;
            init();
        }
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

    maintenance();

}

void UserInterface::menu()
{
    string uIn = ""; //user input
    cout << "_____________________________________________________" << endl;
    cout << "|                 INTERACTIVE MENU                  |" << endl;
    cout << "|___________________________________________________|" << endl;
    cout << "|OPTION: | Exit | Maintenance Menu | Stats | Search |" << endl;
    cout << "|--------|------|------------------|----------------|" << endl;
    cout << "|COMMAND:| exit |       maint      | stats | search |" << endl;
    cout << "|---------------------------------------------------|" << endl;
    cout << "|DESCRIPTION: Add -d to a command to get a          |" << endl;
    cout << "| description of that command. (ex: stats-d)        |" << endl;
    cout << "|___________________________________________________|" << endl << endl;
    cin >> uIn;
    transform(uIn.begin(), uIn.end(), uIn.begin(), ::tolower);

    if(uIn == "dindex")
    {
        if(filesParsed == 0)
        {
                cout << "Index is empty, please add opinions in the maintenance menu." << endl;
                menu();
        }
        else
        {
          index->displayI();
          menu();
        }

    }
    else if(uIn == "maint")
    {
        maintenance();
    }
    else if(uIn == "stats")
    {
        if(filesParsed == 0)
        {
           cout << "Index is empty, please add opinions in the maintenance menu." << endl;
           menu();
        }
        else
         {
            cout << "Number of files parsed: " << filesParsed << endl;
            cout << "Number of unique words: " << index->getUWords() << endl;
            menu();
          }
    }
    else if(uIn == "exit")
        return;
    else if(uIn == "search")
    {
        string search;
        vector<string> results;
        cout << "Please Enter your search: ";
        cin >> search;
        QueryProcessor q(search, index);
        results = q.search();
        cout << "Documents with your query:" << endl;
        for(int i = 0; i < results.size(); i++)
        {
            cout << results[i] << endl;
        }
        menu();

    }
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
