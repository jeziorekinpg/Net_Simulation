#ifndef NET_SIMULATION_STORAGE_TYPES_HPP
#define NET_SIMULATION_STORAGE_TYPES_HPP

#include <deque>
#include <list>
#include "package.hpp"

enum class PackageQueueType {
    FIFO,
    LIFO
};

class IPackageStockpile {
public:
    using contener_type = std::list<Package>;
    using own_iterator = contener_type::const_iterator;

    virtual void push(Package&&) = 0;

    virtual const bool empty() = 0;

    virtual const size_type size() = 0;

    virtual own_iterator begin() = 0;

    virtual own_iterator begin() const = 0;

    virtual own_iterator end() = 0;

    virtual own_iterator end() const = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual const PackageQueueType get_queue_type() = 0;
};

class PackageQueue : public IPackageQueue {
public:
    void push(Package&&) override;

    const bool empty() override;

    const size_type size() override;

    own_iterator begin() override { return list_.begin(); }

    own_iterator begin() const override { return list_.cbegin(); }

    own_iterator end() override { return list_.end(); }

    own_iterator end() const override { return list_.cend(); }

    Package pop() override;

    const PackageQueueType get_queue_type() override;

    explicit PackageQueue(const PackageQueueType type) : type_(type) {}


private:
    PackageQueueType type_;
    contener_type list_;

};

#endif
