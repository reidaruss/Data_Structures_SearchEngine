#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iostream>
#include "indexinterface.h"
#include <string>

using namespace std;

class QueryProcessor
{
private:
    vector<string> query;
    IndexInterface *index;
public:
    QueryProcessor(string s, IndexInterface* ind);

    vector<string> search();
    vector<string> regSearch();
    vector<string> andS(int x);
    vector<string> orS(int x);
    vector<string> notS(int x);
};

#endif // QUERYPROCESSOR_H
