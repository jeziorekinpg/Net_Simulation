#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "helpers.hpp"
#include <optional>
#include <memory>
#include <functional>

enum class NodeType {
    WORKER,
    STOREHOUSE,
    RAMP
};

class IPackageReceiver {
public:
    virtual void receive_package(Package&&) const = 0;
    virtual ElementID get_id() const = 0;

    virtual IPackageStockpile::const_iterator begin() const = 0;

    virtual IPackageStockpile::const_iterator end() const = 0;
};

class ReceiverPreferences {
public:
    ReceiverPreferences();
    ReceiverPreferences(ProbabilityGenerator);
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
protected:
    ProbabilityGenerator probability_generator_;
};

class PackageSender {
public:
    PackageSender(ReceiverPreferences&&);
    ReceiverPreferences receiver_preferences_;
    void send_package() {};

    const std::optional<Package> get_sending_buffer();
protected:
    void push_package(Package&&);
};

class Storehouse : public IPackageStockpile, IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) { id_ = id, d_ = std::move(d); }
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};

class Worker : public IPackageReceiver, PackageSender {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) { id_ = id, pd_ = pd, q_ = std::move(q); }
    void do_work(Time t) {};
    TimeOffset get_processing_duration() const {};
    Time get_package_processing_start_time() const {};
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
};

class Ramp : public PackageSender{
public:
    Ramp(ReceiverPreferences&&, ElementID, TimeOffset);
    void deliver_goods(Time t) {};
    TimeOffset get_delivery_interval() const { return di_; }
    ElementID get_id() const { return id_; }
private:
    ElementID id_;
    TimeOffset di_;
    NodeType type_;
};

#endif //NET_SIMULATION_NODES_HPP
