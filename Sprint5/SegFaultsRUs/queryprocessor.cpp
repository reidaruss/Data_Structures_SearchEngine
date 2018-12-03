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
    vector<string> result = index->searchIndex(q); //change all search functions to accept string instead of vector.
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
    return result;
}

vector<string> QueryProcessor::andS(int x)
{
    vector<string> result;
    vector<vector<string>> doccmp;
    vector<string> notv;
    for(int i = x; i < query.size(); i++)
    {
        if(query[i] != "OR" && query[i] != "NOT")
        {
            vector<string> temp = regSearch(query[i]);
            doccmp.push_back(temp);
        }
        else
        {
            if(query[i] == "NOT")
                notv = regSearch(query[i]);
        }


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

    return result;
}

vector<string> QueryProcessor::orS(int x)
{
    vector<string> result;
    vector<vector<string>> doccmp;
    for(int i = x; i < query.size(); i++)
    {
        if(query[i] != "AND" && query[i] != "NOT")
        {
            vector<string> temp = regSearch(query[i]);
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
    return result;
}

vector<string> QueryProcessor::notS(int x)
{
    vector<string> result;
    vector<string> temp1 = regSearch(query[0]);
    vector<string> temp2 = regSearch(query[2]);
    for(int i = 0; i < temp1.size(); i++)
    {
        for(int j = 0; j < temp2.size(); j++)
        {
            if(temp1[i] != temp2[j] && j == temp2.size()-1)
                result.push_back(temp1[i]);
        }
    }
    return result;
}
