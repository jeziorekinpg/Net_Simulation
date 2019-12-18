#ifndef NET_SIMULATION_STORAGE_TYPES_HPP
#define NET_SIMULATION_STORAGE_TYPES_HPP

#include <deque>
#include <list>
#include "package.hpp"

enum class PackageQueueType{
    FIFO,
    LIFO
};

class IPackageStockpile {
public:
    using contener_type = std::list<Package>;
    using own_iterator = contener_type::const_iterator;
    virtual const void push(Package&&) = 0;
    virtual const bool empty() = 0;
    virtual const size_type size() = 0;
    own_iterator begin() {return list_.begin();}
    own_iterator begin() const {return list_.cbegin();}
    own_iterator end() {return list_.end();}
    own_iterator end() const {return list_.cend();}

};

class IPackageQueue: public IPackageStockpile{
public:
    virtual Package&& pop() = 0;
    virtual const PackageQueueType get_queue_type() = 0;
};

class PackageQueue: public IPackageQueue {
public:
    explicit PackageQueue(const PackageQueueType type);
    const void push(Package&&) override;
    Package&& pop() override;

private:
    PackageQueueType type_;
    std::list<Package> list_;

};

#endif
