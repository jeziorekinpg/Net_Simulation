#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include <_bsd_types.h>

class Package{
public:
    Package(const u_int id) : id_(id) {}
    Package() = default;
    Package(Package&&) = default; // Package(const Package&&) = default; wywala blad
    Package& operator=(const Package&&); //'operator=' is not implemented ??
    typename ElementID get_id() const {return _id}

private:
    u_int id_;
};
#endif
