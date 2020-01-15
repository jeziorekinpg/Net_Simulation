#include "factory.hpp"
#include <map>

bool Factory::is_consistent() const {
    std::map<PackageSender*, NodeColor> color;

    for(const auto& element: list_ramp) {
        color[(PackageSender *) &element] = NodeColor::UNVISITED;
    }

    for(const auto& element: list_worker) {
        color[(PackageSender *) &element] = NodeColor::UNVISITED;
    }

    for(const auto& element: list_ramp) {

        try {
            has_reachable_storehouse(&element, color)
            return true;
        }
        catch(NoReceiverException&, noReceiversException) {
            return false;
        }
    }
    return true;
};
