/*REID RUSSELL
 * The Query Processor takes an input from the user in the UI then parses it
 * and runs the desired search method based on the query. It then returns a vector
 * containing all of the document names the query appears on in a relavency ranked
 * order.
 *
 * -Added regular (1 word) search
 *
 * */
#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
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
    vector<string> regSearch(string q);
    vector<string> andS(int x);
    vector<string> orS(int x);
    vector<string> notS(int x);
};

#endif // QUERYPROCESSOR_H
