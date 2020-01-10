#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "helpers.hpp"
#include <optional>
#include <memory>
#include <functional>
#include <map>

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
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
public:
    ReceiverPreferences();

    ReceiverPreferences(ProbabilityGenerator);

    void add_receiver(IPackageReceiver* r);

    void remove_receiver(IPackageReceiver* r);

    IPackageReceiver* choose_receiver();

protected:
    ProbabilityGenerator probability_generator_;
private:
    preferences_t preferences;
};

class PackageSender {
public:
    PackageSender(PackageSender&&)=default;
    PackageSender(ReceiverPreferences&& receiver);

    ReceiverPreferences receiver_preferences_;

    void send_package();

    const std::optional<Package> get_sending_buffer();

protected:
    void push_package(Package&&);
private:
    std::optional<Package> buffer_;
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
    Worker(ElementID, TimeOffset, std::unique_ptr<IPackageQueue>, ReceiverPreferences&&);
    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return st_; }
private:
    std::optional<Package> buffer;
    ElementID id_;
    Time st_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    NodeType type_;
};

class Ramp : public PackageSender {
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
