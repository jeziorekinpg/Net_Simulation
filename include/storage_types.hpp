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

    virtual void push(Package &&) = 0;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual size_type size() const = 0;

    [[nodiscard]] virtual const_iterator begin() const = 0;

    [[nodiscard]] virtual const_iterator cbegin() const = 0;

    [[nodiscard]] virtual const_iterator end() const = 0;

    [[nodiscard]] virtual const_iterator cend() const = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    [[nodiscard]] virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue : public IPackageQueue {
public:
    void push(Package &&) override;

    [[nodiscard]] bool empty() const override;

    [[nodiscard]] size_type size() const override;

    [[nodiscard]] const_iterator begin() const override { return list_.begin(); }

    [[nodiscard]] const_iterator cbegin() const override { return list_.cbegin(); }

    [[nodiscard]] const_iterator end() const override { return list_.end(); }

    [[nodiscard]] const_iterator cend() const override { return list_.cend(); }

    Package pop() override;

    [[nodiscard]] PackageQueueType get_queue_type() const override;

    explicit PackageQueue(const PackageQueueType type) : type_(type) {}


private:
    PackageQueueType type_;
    contener_type list_;

};

#endif

