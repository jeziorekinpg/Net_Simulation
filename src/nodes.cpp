#include "nodes.hpp"

Ramp::Ramp(ElementID id, TimeOffset di) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}