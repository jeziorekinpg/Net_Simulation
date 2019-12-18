#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include <set>
#include "types.hpp"


class Package {
public:
    Package();

    Package(Package&& pack) : id_(std::move(pack.id_)) {}

    ~Package();

    Package& operator=(Package&&) = default;

    ElementID get_id() const { return id_; }

private:
    int id_;

    static std::set<ElementID> freed_IDs;
    static std::set<ElementID> assigned_IDs;

};

#endif
