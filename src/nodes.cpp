#include "nodes.hpp"


Ramp::Ramp(ElementID id, TimeOffset di) {
    id_ = id;
    di_ = di;
    sender_ = PackageSender();
    typ_ = RAMP;
}