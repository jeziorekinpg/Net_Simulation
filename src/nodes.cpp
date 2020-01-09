#include "nodes.hpp"

Ramp::Ramp(ReceiverPreferences&& receiver, ElementID id, TimeOffset di) : PackageSender(std::move(receiver)) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}

PackageSender::PackageSender(ReceiverPreferences&& receiver) {
    receiver_preferences_ = std::move(receiver);

}


ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator probability_gen) {
    probability_generator_ = probability_gen;
}

ReceiverPreferences::ReceiverPreferences() {
    probability_generator_ = probability_generator;
}

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if(preferences_t.empty()) {
        preferences_t[r] = 1;
    }else{
        for(auto element : preferences_t){
            element.second = 1/preferences_t.size()+1;
        }
        preferences_t[r] = 1/preferences_t.size()+1;

    }
}
