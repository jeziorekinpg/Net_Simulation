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

  typename NodeCollection<Node>::iterator find_by_id(ElementID id_) {
      auto it = std::find_if(container.begin(), container.end(), [id_](const aout &elem) { return (elem.get_id() == id_); })
      return it;
  }
  typename NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {
      auto it = std::find_if(container.begin(), container.end(), [id_](const aout& elem) {return (elem.get_id() == id_) ;})
      return it;
  }

  void add(Node &node){container.push_back(std::move(node))};
  void remove_by_id(ElementID id_){container.erase(find_by_id(id_))};

private:
  container_t container;
}

class Factory{
public:
  void add_ramp(Ramp && r) {list_ramp.push_back(r);};
  void remove_ramp(ElementID id) {list_ramp.erase(find_ramp_by_id(id))};
  NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return list_ramp.find_by_id(id)};
  NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return list_ramp.find_by_id(id)};
  NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return list_ramp.cbegin()};
  NodeCollection<Ramp>::const_iterator ramp_cend() const {return list_ramp.cend();};

  void add_worker(Worker && w) {list_worker.push_back(w);};
  void remove_worker(ElementID id) {list_worker.erase(find_worker_by_id(id))};
  NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return list_worker.find_by_id(id);};
  NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return list_worker.find_by_id(id)};
  NodeCollection<Worker>::const_iterator worker_cbegin() {return list_worker.cbegin();};
  NodeCollection<Worker>::const_iterator worker_cend() {return list_worker.cend();};

  void add_storehouse(Storehouse && s) {list_storehouse.push_back(s);};
  void remove_storehouse(ElementID id) {list_storehouse.erase(find_storehouse_by_id(id))};
  NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return list_storehouse.find_by_id(id)};
  NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return list_storehouse.find_by_id(id)};
  NodeCollection<Storehouse>::const_iterator storehouse_cbegin() {return list_storehouse.cbegin();};
  NodeCollection<Storehouse>::const_iterator storehouse_cend() {return list_storehouse.cend();};

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
