#ifndef NET_SIMULATION_FACTORY_HPP
#define NET_SIMULATION_FACTORY_HPP

#include "nodes.hpp"

enum class NodeColor {
    UNVISITED,
    VISITED,
    VERIFIED
};

bool has_reachable_storehouse(const PackageSender *, std::map<const PackageSender *, NodeColor> &);

template<typename Node>
class NodeCollection {
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    [[nodiscard]] iterator begin() { return container.begin(); };

    [[nodiscard]] iterator end() { return container.end(); };

    [[nodiscard]] const_iterator begin() const { return container.begin(); };

    [[nodiscard]] const_iterator end() const { return container.end(); };

    [[nodiscard]] const_iterator cbegin() const { return container.cbegin(); };

    [[nodiscard]] const_iterator cend() const { return container.cend(); };

    typename NodeCollection<Node>::iterator find_by_id(ElementID id_) {
        auto it = std::find_if(container.begin(), container.end(),
                               [id_](auto& elem) { return (elem.get_id() == id_); });
        return it;
    }

    [[nodiscard]] typename NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {
        auto it = std::find_if(container.begin(), container.end(),
                               [id_](const auto& elem) { return (elem.get_id() == id_); });
        return it;
    }

    void add(Node& node) { container.push_back(std::move(node)); };

    void remove_by_id(ElementID id_) {
      auto i = find_by_id(id_);
      if(i != container.end()) {container.erase(i);}
    };

private:
    container_t container;
};

class Factory {
public:
    void add_ramp(Ramp&& r) { list_ramp.add(r); };

    void remove_ramp(ElementID id);

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return list_ramp.find_by_id(id); };

    [[nodiscard]] NodeCollection<Ramp>::const_iterator
    find_ramp_by_id(ElementID id) const { return list_ramp.find_by_id(id); };

    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return list_ramp.cbegin(); };

    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_cend() const { return list_ramp.cend(); };

    void add_worker(Worker&& w) { list_worker.add(w); };

    void remove_worker(ElementID id);

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return list_worker.find_by_id(id); };

    [[nodiscard]] NodeCollection<Worker>::const_iterator
    find_worker_by_id(ElementID id) const { return list_worker.find_by_id(id); };

    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_cbegin() const { return list_worker.cbegin(); };

    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_cend() const { return list_worker.cend(); };

    void add_storehouse(Storehouse&& s) { list_storehouse.add(s); };

    void remove_storehouse(ElementID id);

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return list_storehouse.find_by_id(id); };

    [[nodiscard]] NodeCollection<Storehouse>::const_iterator
    find_storehouse_by_id(ElementID id) const { return list_storehouse.find_by_id(id); };

    [[nodiscard]] NodeCollection<Storehouse>::const_iterator
    storehouse_cbegin() const { return list_storehouse.cbegin(); };

    [[nodiscard]] NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return list_storehouse.cend(); };

    [[nodiscard]] bool is_consistent() const;

    void do_deliveries(Time t);

    void do_work(Time t);

    void do_package_passing();


private:


    template <typename Node>
    void remove_receiver(NodeCollection<Node>&, ElementID);


    NodeCollection<Worker> list_worker;
    NodeCollection<Ramp> list_ramp;
    NodeCollection<Storehouse> list_storehouse;
};

#endif // NET_SIMULATION_FACTORY_HPP

