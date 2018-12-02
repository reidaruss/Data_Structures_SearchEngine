#include "queryprocessor.h"

QueryProcessor::QueryProcessor(string s, IndexInterface *ind)
{
    index = ind;
    string tempstr = "";
    istringstream str(s);
    while(getline(str,tempstr,' '))
    {
        query.push_back(tempstr);
    }

}

vector<string> QueryProcessor::search()
{
    for(int i = 0; i < query.size(); i++)
    {
        if(query[i] == "AND")
            return andS(i);
        else if(query[i] == "OR")
            return orS(i);
        else if(query[i] == "NOT")
            return notS(i);
    }
    return regSearch();
}

vector<string> QueryProcessor::regSearch()
{
    vector<string> result = index->searchIndex(query);
    return result;
}

vector<string> QueryProcessor::andS(int x)
{

}

vector<string> QueryProcessor::orS(int x)
{

}

vector<string> QueryProcessor::notS(int x)
{

}
