#include "userinterface.h"

UserInterface::UserInterface()
{
    filesParsed = 0;
    numWords = 0;
    indexType = 0;
    cout << "Welcome to SCOTUS Opinion Search Engine." << endl;
}

/*This function is the initial function call of the program.
 * It reads in the persisted index (if there is one) then prompts
 * the user for which menu they would like to navigate to.
 * */
void UserInterface::start()
{
    PersistedIndex p;
    index = p.readIndex();
    if(index != NULL)
    {
        numWords = index->getSize();
        indexType = p.getIndexType();
        avgW = p.getAVGW();
    }

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

/*This function is the maintenance menu and is responsible for
 * handling adding opinions, clearing the index, switching menus, and exiting the program.
 */
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
        PersistedIndex pI(index);
        pI.writeIndex(indexType, numWords, avgW);
        index->clearIndex();
        delete index;
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
    else if(uIn == "int-d")
    {
        cout << "int: Switch to the Interactive Menu" << endl;
        maintenance();
    }
    else if(uIn == "ci")
    {
        if(numWords == 0)
        {
            cout << "Index already empty. Please add opinions." << endl;
            maintenance();
        }
        else
        {
            index->clearIndex();
            if(index->isEmpty() == true)
                numWords = 0;
            if(numWords == 0)
            {
                cout << "Index Cleared." << endl;
                delete index;
                index = NULL;
                indexType = 0;
                maintenance();
            }
            else
            {
                cerr << "Error Clearing Index.." << endl;
                maintenance();
            }

        }
    }
    else if(uIn == "ci-d")
    {
        cout << "ci: Clears the current index." << endl;
        maintenance();
    }
    else if(uIn == "ao")
    {
        string file;
        cout << "Please Enter A File Path: " ;
        cin >> file;
        if(numWords != 0)
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
    else if(uIn == "ao-d")
    {
        cout << "ao: Add documents to the index with a filepath to a folder containing new opinions." << endl;
        maintenance();
    }
    else
    {
        cerr << "Invalid Entry." << endl;
        maintenance();
    }
}

/*This function is called when new files are being added.
 * It calls the parser and sets the index type to keep track
 * of what type of index it is.
 */
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


    if(indexType == 1 && index == NULL)
    {
        index = new avlindex;
    }
    else if(indexType == 2 && index == NULL)
    {
        index = new htindex;
    }

    parse.setDirectoryHead(filepath);
    parse.readFiles(index);
    filesParsed += parse.getFP();
    numWords += index->getSize();
    avgW += index->getAVGW();
    avgW = avgW/filesParsed;
    maintenance();

}

/*This function is the interactive menu and is responsible for handling user
 * searches, printing statistics, switching menus, displaying the index(hashttable only)
 * and exiting the program.
 */
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
        if(numWords == 0)
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
    else if(uIn == "maint-d")
    {
        cout << "maint: Switches to the Maintenance Menu." << endl;
        menu();
    }
    else if(uIn == "stats")
    {
        if(numWords == 0)
        {
           cout << "Index is empty, please add opinions in the maintenance menu." << endl;
           menu();
        }
        else
         {
            cout << "Number of files parsed: " << filesParsed << endl;
            cout << "Number of unique words: " << index->getUWords() << endl;
            cout << "Average number of words Indexed per Opinion: " << avgW << endl;
            menu();
          }
    }
    else if(uIn == "exit")
    {
        PersistedIndex pI(index);
        pI.writeIndex(indexType,numWords, avgW);
        index->clearIndex();
        delete index;
        return;
    }
    else if(uIn == "search")
    {
        if(numWords == 0)
        {
           cout << "Index is empty, please add opinions in the maintenance menu." << endl;
           menu();
        }
        else
         {
            string search = "";

            vector<string> results;
            cin.get();
            cout << "Please Enter your search: " << endl;
            getline(cin, search);
            transform(search.begin(), search.end(), search.begin(), ::tolower);
            search = parse.stemString(search);
            QueryProcessor q(search, index);
            results = q.search();
            cout << "Documents with your query:" << endl;
            for(int i = 0; i < results.size(); i++)
            {
                cout << results[i] << endl << endl;
            }
            if(results[0] == "No results for query. Please search for another word")
                menu();
            string fileN = "";
            cout << "Enter the file name you would like to open or enter 'b' to go back to menu." << endl;
            cin >> fileN;
            if(fileN == "b"){
                menu();
            }
            else{
                cout << parse.getFileExcerpt(fileN) << endl;
                menu();
            }
        }

    }
    else if(uIn == "search-d")
    {
        cout << "search: Enter a search query and get back the documents containing that query." << endl;
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
