#ifndef NET_SIMULATION_FACTORY_HPP
#define NET_SIMULATION_FACTORY_HPP

#include "nodes.hpp"
enum class NodeColor {
  UNVISITED,
  VISITED,
  VERIFIED
};

enum class ReceiverType {
  WORKER,
  STOREHOUSE
};

bool has_reachable_storehouse(const PackageSender *, std::map<const PackageSender *, NodeColor> &) const;

class NodeCollection<Node> {

  using container_t = typename std::vector<Node>;
  using iterator = typename container_t::iterator;
  using const_iterator = typename container_t::const_iterator;

public:
  iterator begin() {return container_t.begin();};
  iterator end() {return container_t.end();};
  iterator cbegin() const {return container_t.cbegin();};
  iterator cend() const {return container_t.cend();};
  const_iterator cbegin() const {return container_t.cbegin();};
  const_iterator cend() const {return container_t.cend();};
  
  NodeCollection<Node>::iterator find_by_id(ElementID id_) {
      auto it = std::find_if(container.begin(), container.end(), [id_](const aout &elem) { return (elem.get_id() == id_); })
      return it;
  }
  NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {
      auto it = std::find_if(container.begin(), container.end(), [id_](const aout& elem) {return (elem.get_id() == id_) ;})
      return it;
  }

  void add(Node &node){container.push_back(std::move(node))};
  void remove_by_id(ElementID id_){container.erase(find_by_id(id_))};

private:
  container_t container;
}

class Factory {
public:
  void add_ramp(Ramp &&);
  void remove_ramp(ElementID id);
  NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
  NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const;
  NodeCollection<Ramp>::const_iterator ramp_cbegin() const {};
  NodeCollection<Ramp>::const_iterator ramp_cend() const;

  void add_worker(Worker &&);
  void remove_worker(ElementID id)
  NodeCollection<Worker>::iterator find_worker_by_id(ElementID id);
  NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id);                        // const
  NodeCollection<Worker>::const_iterator worker_cbegin(); // const
  NodeCollection<Worker>::const_iterator worker_cend();   // const

  void add_storehouse(Storehouse &&);
  void remove_storehouse(ElementID id);
  NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
  NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id);                            // const
  NodeCollection<Storehouse>::const_iterator storehouse_cbegin(); // const
  NodeCollection<Storehouse>::const_iterator storehouse_cend();   // const

  bool is_consistent() const;
  void do_deliveries(Time);
  void do_package_passing();
  void do_work(Time);

private:
  void remove_receiver(NodeCollection<Node> &collection, ElementID id);

  NodeCollection<Worker> list_worker;
  NodeCollection<Ramp> list_ramp;
  NodeCollection<Storehouse> list_storehouse;
};


#endif // NET_SIMULATION_FACTORY_HPP

