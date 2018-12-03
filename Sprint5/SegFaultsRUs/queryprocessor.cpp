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
    return regSearch(query[0]);
}

vector<string> QueryProcessor::regSearch(string q)
{
    vector<string> noresult;
    noresult.push_back("No results for query. Please search for another word");
    vector<string> result = index->searchIndex(q); //change all search functions to accept string instead of vector.
    if(result.size() ==0)
        return noresult;
    vector<int> freq = index->getFreq(q);
    int temp;
    string tempstr;
    int j;
    for(int i = 0; i < freq.size(); i++)
    {
        j = i+1;
        while(j < freq.size())
        {
            if(freq[i] < freq[j])
            {
                temp = freq[i];
                freq[i] = freq[j];
                freq[j] = temp;

                tempstr = result[i];
                result[i] = result[j];
                result[j] = tempstr;
            }
            j++;
        }
    }
    if(result.size() == 0)
        return noresult;
    else
        return result;
}

vector<string> QueryProcessor::andS(int x)
{
    vector<string> noresult;
    noresult.push_back("No results for query. Please search for another word");
    vector<string> result;
    vector<vector<string>> doccmp;
    vector<string> notv;
    for(int i = x+1; i < query.size(); i++)
    {
        if(query[i] != "OR" && query[i] != "NOT")
        {
            vector<string> temp = regSearch(query[i]);
            if(temp == noresult)
                return noresult;
            doccmp.push_back(temp);
        }
        else
        {
            if(query[i] == "NOT")
                notv = regSearch(query[i]);
        }


    }
    for(int i = 0; i < doccmp.size(); i++)
    {
        if(doccmp[i].size() == 0)
            return noresult;
    }
    //do comparison to see what files contain same words

    for(int i = 0; i < doccmp.size() -1; i++)
    {

        for(int j = 0; j < doccmp[i].size(); j++)
        {
            for(int z = 0; z < doccmp.size(); z++)
            {
                if(z != i)
                {
                    for(int k = 0; k < doccmp[z].size(); k++)
                    {
                        if(doccmp[i][j] == doccmp[z][k])
                        {
                            result.push_back(doccmp[i][j]);
                        }
                    }
                }
            }

        }

    }
    vector<string> altresult;
    for(int i = 0; i < notv.size(); i++)
    {
        for(int j = 0; j < result.size(); j++)
        {
            if(notv[i] != result[j])
                altresult.push_back(result[j]);
        }
        if(i == notv.size()-1)
            return altresult;
    }

    if(result.size() == 0)
        return noresult;
    else
        return result;
}

vector<string> QueryProcessor::orS(int x)
{
    vector<string> noresult;
    noresult.push_back("No results for query. Please search for another word");
    vector<string> result;
    vector<vector<string>> doccmp;
    for(int i = x; i < query.size(); i++)
    {
        if(query[i] != "AND" && query[i] != "NOT")
        {
            vector<string> temp = regSearch(query[i]);
            if(temp == noresult)
                return noresult;
            doccmp.push_back(temp);
        }

    }
    result.push_back(doccmp[0][0]);
    for(int i = 0; i < doccmp.size(); i++)
    {
        for(int j = 0; j < doccmp[i].size(); j++)
        {
            for(int k = 0; k < result.size(); k++)
            {
                if(doccmp[i][j] != result[k] && k == result.size()-1)
                     result.push_back(doccmp[i][j]);
            }

        }
    }
    if(result.size() == 0)
        return noresult;
    else
        return result;
}

vector<string> QueryProcessor::notS(int x)
{
    vector<string> noresult;
    noresult.push_back("No results for query. Please search for another word");
    vector<string> result;
    vector<string> temp1 = regSearch(query[0]);
    vector<string> temp2 = regSearch(query[2]);
    if(temp1 == noresult)
        return noresult;
    else if(temp2 == noresult)
        return temp1;
    for(int i = 0; i < temp1.size(); i++)
    {
        for(int j = 0; j < temp2.size(); j++)
        {
            if(temp1[i] != temp2[j] && j == temp2.size()-1)
                result.push_back(temp1[i]);
        }
    }
    if(result.size() == 0)
        return noresult;
    else
        return result;
}
