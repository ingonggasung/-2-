#include "MSList.h"

MSList::MSList() {}

MSList::~MSList() {
    for (auto obj : objects) {
        delete obj;
    }
}

void MSList::add(MObject* obj) {
    objects.push_back(obj);
}

void MSList::renderAll() {
    for (auto obj : objects) {
        obj->render();
    }
}
