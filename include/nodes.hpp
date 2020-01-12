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
    virtual void receive_package(Package &&) = 0;
    //[[nodiscard]] virtual ReceiverType get_receiver_type() const = 0;

    [[nodiscard]] virtual ElementID get_id() const = 0;

    [[nodiscard]] virtual IPackageStockpile::const_iterator begin() const = 0;

    [[nodiscard]] virtual IPackageStockpile::const_iterator cbegin() const = 0;

    [[nodiscard]] virtual IPackageStockpile::const_iterator end() const = 0;

    [[nodiscard]] virtual IPackageStockpile::const_iterator cend() const = 0;
};

class ReceiverPreferences {
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;
public:
    ReceiverPreferences();

    explicit ReceiverPreferences(ProbabilityGenerator);

    void add_receiver(IPackageReceiver *r);

    void remove_receiver(IPackageReceiver *r);

    const preferences_t& get_preferences() const { return preferences; }

    IPackageReceiver *choose_receiver();

protected:
    ProbabilityGenerator probability_generator_;
private:
    preferences_t preferences;
};

class PackageSender {
public:
    PackageSender(PackageSender &&) = default;

    PackageSender();

    explicit PackageSender(ReceiverPreferences &&receiver);

    ReceiverPreferences receiver_preferences_;

    void send_package();

    [[nodiscard]] std::optional<Package> &get_sending_buffer() const;

protected:
    void push_package(Package &&);

private:
    std::optional<Package> buffer_;
};


class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d);

    [[nodiscard]] IPackageStockpile::const_iterator begin() const override { return d_->cbegin(); }

    [[nodiscard]] IPackageStockpile::const_iterator cbegin() const override { return d_->begin(); }

    [[nodiscard]] IPackageStockpile::const_iterator end() const override { return d_->cend(); }

    [[nodiscard]] IPackageStockpile::const_iterator cend() const override { return d_->end(); }

    //[[nodiscard]] ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; }

    [[nodiscard]] ElementID get_id() const override { return id_; }

    void receive_package(Package &&p) override { d_->push(std::move(p)); }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    NodeType type_;
};

class Worker : public IPackageReceiver, public PackageSender {
public:
    Worker(ElementID, TimeOffset, std::unique_ptr<IPackageQueue>, ReceiverPreferences &&);
    Worker(ElementID, TimeOffset, std::unique_ptr<IPackageQueue>);

    void do_work(Time t);

    [[nodiscard]] IPackageStockpile::const_iterator begin() const override { return q_->cbegin(); }

    [[nodiscard]] IPackageStockpile::const_iterator cbegin() const override { return q_->begin(); }

    [[nodiscard]] IPackageStockpile::const_iterator end() const override { return q_->cend(); }

    [[nodiscard]] IPackageStockpile::const_iterator cend() const override { return q_->end(); }

    [[nodiscard]] TimeOffset get_processing_duration() const { return pd_; }

    [[nodiscard]] Time get_package_processing_start_time() const { return st_; }

    [[nodiscard]] ElementID get_id() const override { return id_; }

    void receive_package(Package &&p) override { q_->push(std::move(p)); }

private:
    std::optional<Package> buffer;
    ElementID id_;
    Time st_{};
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    NodeType type_;
};

class Ramp : public PackageSender {
public:
    Ramp(ElementID, TimeOffset, ReceiverPreferences &&);

    Ramp(ElementID, TimeOffset);

    void deliver_goods(Time t);

    [[nodiscard]] TimeOffset get_delivery_interval() const { return di_; }

    [[nodiscard]] ElementID get_id() const { return id_; }

private:
    ElementID id_;
    TimeOffset di_;
    NodeType type_;
};

#endif //NET_SIMULATION_NODES_HPP
