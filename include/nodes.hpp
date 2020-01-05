//
// Created by Imperator on 04.01.2020.
//

#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#include "package.hpp"
#include "storage_types.hpp"
#include <optional>

enum class NodeType{
    WORKER;
    STOREHOUSE;
    RAMP;
};

class Storehouse : public IPackageStockpile, IPackageReceiver{
public:
    Storehouse(id: ElementID, d: std::unique_ptr<IPackageStockpile);
};

class Worker : public IPackageReceiver, PackageSender, IPackageQueue{
public:
    void Worker(id: ElementID, pd: TimeOffset, q: std::unique_ptr<IPackageQueue>) {};
    void do_work(t: Time) {};
    const TimeOffset get_processing_duration() {};
    const Time get_package_processing_start_time() {};

};

class IPackageReceiver {
public:

    virtual const void receive_package(Package&&) = 0;
;
};    virtual const ElementID get_id() = 0

class Ramp : public PackageSender{
public:
    void Ramp(id: ElementID, di: TimeOffset) {};
    void deliver_goods(t: Time) {};
    const TimeOffset get_delivery_interval() {};
    const ElementID get_id() {};
};

class PackageSender : public ReceiverPreferences{
public:
    void send_package() {};
    const std::optional<Package> get_sending_buffer() {};
private:
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&&) {};
};

class ReceiverPreferences {
public:
    ReceiverPreferences(pg: ProbabilityGenerator);
    void add_receiver(r: IPackageReceiver*) {};
    void remove_receiver(r: IPackageReceiver*) {};
    IPackageReceiver* choose_receiver() {};

};

#endif //NET_SIMULATION_NODES_HPP
