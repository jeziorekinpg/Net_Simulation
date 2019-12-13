#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include <_bsd_types.h>

class Package{
public:
    Package(u_int id) : id_(id) {}
    Vehicle(const Vehicle&&) = default;
    Package& operator=(const Package&&);
    typename ElementID get_id() const {return _id}

private:
    u_int id_;
};
#endif
