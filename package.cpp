#include "package.hpp"


std::set<ElementID> Package::freed_IDs;
std::set<ElementID> Package::assigned_IDs{0};

// trzeba dodac opcję, żeby kostruktor i destruktor pracował z tymi listami
Package::Package() {
    if (freed_IDs.empty()) {
        id_ = *assigned_IDs.cend() + 1;
    }else{
        id_ = *freed_IDs.cbegin();
        freed_IDs.erase(freed_IDs.cbegin());
    }

}

Package::~Package() {
    freed_IDs.insert(id_);
}
