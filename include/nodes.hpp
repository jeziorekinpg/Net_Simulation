#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include <optional>


class IPackageReceiver {
public:
    virtual const void receive_package(Package&&) = 0;
    virtual const ElementID get_id() = 0;
};

class ReceiverPreferences {
public:
    ReceiverPreferences(ProbabilityGenerator());
    void add_receiver(IPackageReceiver* r) {};
    void remove_receiver(IPackageReceiver* r) {};
    IPackageReceiver* choose_receiver() {};

};

class PackageSender : public ReceiverPreferences{
public:
    void send_package() {};
    const std::optional<Package> get_sending_buffer() {};
private:
    ReceiverPreferences receiver_preferences_;
protected:
    void push_back(Package&&) {};
};

class Storehouse : public IPackageStockpile, IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d);
};

class Worker : public IPackageReceiver, PackageSender, IPackageQueue {
public:
    void Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);
    void do_work(Time t) {};
    const TimeOffset get_processing_duration() {};
    const Time get_package_processing_start_time() {};

};

class Ramp : public PackageSender{
public:
    void Ramp(ElementID id, TimeOffset di) {};
    void deliver_goods(Time t) {};
    const TimeOffset get_delivery_interval() {};
    const ElementID get_id() {};
};

#endif //NET_SIMULATION_NODES_HPP
