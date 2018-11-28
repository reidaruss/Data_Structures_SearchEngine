#include "userinterface.h"

UserInterface::UserInterface()
{
    init();
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
}
