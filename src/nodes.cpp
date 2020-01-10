#include "nodes.hpp"

// ReceiverPreferences

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator probability_gen) {
    probability_generator_ = probability_gen;
}

ReceiverPreferences::ReceiverPreferences() {
    probability_generator_ = probability_generator;
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if (preferences.empty()) {
        preferences[r] = 1;
    } else {
        for (auto element : preferences) {
            element.second = 1 / preferences.size() + 1;
        }
        preferences[r] = 1 / preferences.size() + 1;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    if (preferences.find(r) != preferences.end()) {
        preferences.erase(r);
        for (auto element : preferences) {
            element.second = 1 / preferences.size();
        }
    } else {
        throw std::invalid_argument("There is no such receiver");
    }
}

// PackageSender

PackageSender::PackageSender(ReceiverPreferences&& receiver) {
    receiver_preferences_ = std::move(receiver);

}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double wylosowane = probability_generator_();
    double suma = 0.0;
//TODO sprawdzić poprawnośc tej metody
    for (auto element : preferences) {
        suma += element.second;
        if (suma > wylosowane) {
            return (element.first);
        }

    }


}


Ramp::Ramp(ReceiverPreferences&& receiver, ElementID id, TimeOffset di) : PackageSender(std::move(receiver)) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}





