#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include <set>
#include "types.hpp"


class Package{
public:
    Package(const ElementID id) : id_(id) {}
    Package() = default;
    Package(ElementID&& id) : id_(std::move(id)) {} //Moim zdanie chodziło o to, żeby móc id zawłaszczyć, a nie inny produkt. Package(const Package&&) = default; wywala blad
    Package& operator=(Package&&) = default; //'operator=' is not implemented ??
    ElementID get_id() const {return id_;}

private:
    ElementID id_;
};

extern std::set<int> freed_IDs;
extern std::set<int> assigned_IDs;
#endif
