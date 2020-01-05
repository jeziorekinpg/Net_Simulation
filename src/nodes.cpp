#include "nodes.hpp"

Ramp::Ramp(ReceiverPreferences&& receiver, ElementID id, TimeOffset di) : PackageSender(std::move(receiver)) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}

PackageSender::PackageSender(ReceiverPreferences&& receiver) {
    receiver_preferences_ = std::move(receiver);

}


ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator probability_generator) {
    probability_generator_ = probability_generator;
}

ReceiverPreferences::ReceiverPreferences() {
    probability_generator_ = probability_generator();
}
