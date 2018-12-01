#include "avlindex.h"

avlindex::avlindex()
{

}


vector<string> avlindex::searchIndex(vector<string> query)
{

}

void avlindex::insertI(string s, string d)
{
    tree.insert(s);
}

void avlindex::displayI()
{
//display something
}

int avlindex::getUWords()
{
    return tree.getSize();
}

bool avlindex::isEmpty()
{
    return tree.isEmpty();
}
