#ifndef MSLIST_H
#define MSLIST_H

#include "MObject.h"
#include <vector>

class MSList {
public:
    MSList();
    ~MSList();

    void add(MObject* obj);
    void renderAll();

private:
    std::vector<MObject*> objects;
};

#endif // MSLIST_H
