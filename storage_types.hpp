#ifndef NET_SIMULATION_STORAGE_TYPES_HPP
#define NET_SIMULATION_STORAGE_TYPES_HPP

#include <deque>
#include <list>
#include "package.hpp"


class IPackageStockpile {
public:
    virtual const void push(Package&&) = 0;
    virtual const bool empty() = 0;
    virtual const size_type size() = 0;
    std::deque<ElementID> begin() {return .begin();}
    std::deque<ElementID> begin() const {return .cbegin();}
    std::deque<ElementID> end() {return .end();}
    std::deque<ElementID> end() const {return .cend();}
};

enum class PackageQueueType{
    FIFO,
    LIFO
};

class IPackageQueue: public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual const PackageQueueType get_queue_type() = 0;
};

class PackageQueue: public IPackageQueue {
public:
    explicit PackageQueue(const PackageQueueType type): type_(type) {}

private:
    PackageQueueType type_;
    std::list<Package> list_;
};

#endif
