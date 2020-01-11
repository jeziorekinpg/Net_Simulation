#ifndef NET_SIMULATION_FACTORY_HPP
#define NET_SIMULATION_FACTORY_HPP

enum class ReceiverType {
    WORKER,
    STOREHOUSE
};

enum class NodeColor {
    UNVISITED,
    VISITED,
    VERIFIED
};

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);
bool Factory::is_consistent();

class NodeCollection<Node> {
    using container_t = typename std_container_t<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node& node);
    void remove_by_id(ElementID id_);
    NodeCollection<Node>::iterator find_by_id(ElementID id_);
    NodeCollection<Node>::const_iterator find_by_id(ElementID id_); // const
};

class Factory {
public:
    void add_ramp(Ramp&&);
    void remove_ramp(ElementID id);

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id); //const
    NodeCollection<Ramp>::const_iterator ramp_cbegin(); //const
    NodeCollection<Ramp>::const_iterator ramp_cend(); //const

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id); //const
    NodeCollection<Worker>::const_iterator worker_cbegin(); //const
    NodeCollection<Worker>::const_iterator worker_cend(); //const

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id); //const
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin(); //const
    NodeCollection<Storehouse>::const_iterator storehouse_cend(); //const

    bool is_consistent();
    void do_deliveries(Time);
    void do_package_passing();
    void do_work(Time);
private:
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};
#endif //NET_SIMULATION_FACTORY_HPP
