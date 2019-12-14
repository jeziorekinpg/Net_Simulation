#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include "types.hpp"

class Package{
public:
    Package(const ElementID id) : id_(id) {}
    Package() = default;
    Package(Package&&) = default; // Package(const Package&&) = default; wywala blad
    Package& operator=(const Package&&); //'operator=' is not implemented ??
    ElementID get_id() const {return id_;}

private:
    ElementID id_;
};
#endif
