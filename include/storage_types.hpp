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
    using const_iterator = contener_type::const_iterator;

    virtual void push(Package&&) = 0;

    virtual bool empty() const = 0;

    virtual size_type size() const = 0;

    virtual const_iterator begin() = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator end() = 0;

    virtual const_iterator end() const = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue : public IPackageQueue {
public:
    void push(Package&&) override;

    bool empty() const override;

    size_type size() const override;

    const_iterator begin() override { return list_.begin(); }

    const_iterator begin() const override { return list_.cbegin(); }

    const_iterator end() override { return list_.end(); }

    const_iterator end() const override { return list_.cend(); }

    Package pop() override;

    PackageQueueType get_queue_type() const override;

    explicit PackageQueue(const PackageQueueType type) : type_(type) {}


private:
    PackageQueueType type_;
    contener_type list_;

};

#endif
