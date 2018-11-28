//Reid Russell
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H


class IndexInterface
{
public:
    IndexInterface();
    virtual void createIndex() = 0;
    virtual void searchIndex() = 0;

};

#endif // INDEXINTERFACE_H
