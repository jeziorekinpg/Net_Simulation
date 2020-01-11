#include "nodes.hpp"

#include <utility>

// ReceiverPreferences

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator probability_gen) {
    probability_generator_ = std::move(probability_gen);
}

ReceiverPreferences::ReceiverPreferences() {
    probability_generator_ = probability_generator;
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if (preferences.empty()) {
        preferences[r] = 1;
    } else {
        for (auto& element : preferences) {
            element.second = 1.0 / preferences.size() + 1;
        }
        preferences[r] = 1.0 / preferences.size() + 1;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    if (preferences.find(r) != preferences.end()) {
        preferences.erase(r);
        for (auto& element : preferences) {
            element.second = 1.0 / preferences.size();
        }
    } else {
        throw std::invalid_argument("There is no such receiver");
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double wylosowane = probability_generator_();
    double suma = 0.0;
    IPackageReceiver* to_return = nullptr;
//TODO sprawdzic poprawnosc tej metody
    for (auto& element : preferences) {
        suma += element.second;
        if (suma > wylosowane) {
            to_return = element.first;
            break;
        }
    }
    return (to_return);
}

// PackageSender

PackageSender::PackageSender(ReceiverPreferences&& receiver) {
    receiver_preferences_ = std::move(receiver);
    buffer_ = std::nullopt;
}

void PackageSender::send_package() {
    if (buffer_.has_value()) {
        IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(buffer_.value()));
        buffer_.reset();
    }

}

std::optional<Package>& PackageSender::get_sending_buffer() const {
    return (std::optional<Package>&) buffer_;

}

void PackageSender::push_package(Package&& to_send) {
    if (buffer_.has_value()) {
        throw std::invalid_argument("Buffer is already full");
    } else {
        buffer_ = std::move(to_send);
    }
}


Ramp::Ramp(ReceiverPreferences&& receiver, ElementID id, TimeOffset di) : PackageSender(std::move(receiver)) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}


void Ramp::deliver_goods(Time t) {
    if ((t == 1) || (t % Ramp::di_ == 1)) {
        PackageSender::push_package(Package());
    }
}


void Worker::do_work(Time t) {
    if (!buffer.has_value()) {
        buffer = q_->pop();
        st_ = t;
    }
    if (t == st_ + pd_) {
        push_package(std::move(buffer.value()));
        buffer.reset();
        st_ = 0;
    }
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q, ReceiverPreferences&& receiver)
        : PackageSender(std::move(receiver)) {
    id_ = id, pd_ = pd, q_ = std::move(q);
    type_ = NodeType::WORKER;

}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender(ReceiverPreferences()){
    id_ = id, pd_ = pd, q_ = std::move(q);
    type_ = NodeType::WORKER;
}

Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::FIFO))) {
  id_ = id,
  d_ = std::move(d);
  type_ = NodeType::STOREHOUSE;
}
