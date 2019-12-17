#include "package.hpp"


std::set<ElementID> Package::freed_IDs;
std::set<ElementID> Package::assigned_IDs{0};


Package::Package() {
    if (freed_IDs.empty()) {
        id_ = *assigned_IDs.cend() + 1;
        assigned_IDs.insert(id_);
    }else{
        id_ = *freed_IDs.cbegin();
        assigned_IDs.insert(id_);
        freed_IDs.erase(freed_IDs.cbegin());
    }

}

Package::~Package() {
    assigned_IDs.erase(assigned_IDs.find(id_));
    freed_IDs.insert(id_);
}
