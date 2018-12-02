#include "avlindex.h"

avlindex::avlindex()
{}


vector<string> avlindex::searchIndex(vector<string> query)
{

    return tree.getDocs(query);
}

void avlindex::insertI(string s, string d)
{
    if(tree.search(s) == true)
    {
        tree.addDoc(s, d);
    }
    else if(tree.search(s) == false)
    {
        tree.insert(s,d);
    }
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

void avlindex::clearIndex()
{
    tree.clearTree();
}

int avlindex::getSize()
{
    return tree.getSize();
}

vector<string> avlindex::getIndex()
{
    return tree.getIndex();
}

vector<int> avlindex::getFreq(vector<string> query)
{

}
