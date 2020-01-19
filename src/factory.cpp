#include "factory.hpp"
#include <map>

void Factory::do_deliveries(Time t) {
    for (auto iter = list_ramp.begin(); iter != list_ramp.end(); iter++) {
        iter->deliver_goods(t);
    }
}

void Factory::do_work(Time t) {
    for (auto iter = list_worker.begin(); iter != list_worker.end(); iter++) {
        iter->do_work(t);
    }
}

void Factory::do_package_passing() {
    for (auto iter = list_ramp.begin(); iter != list_ramp.end(); iter++) {
        iter->send_package();
    }
    for (auto iter = list_worker.begin(); iter != list_worker.end(); iter++) {
        iter->send_package();
    }
}

void Factory::remove_worker(ElementID id) {
    remove_receiver(list_worker, id);
    list_worker.remove_by_id(id);
}

void Factory::remove_ramp(ElementID id) {
    list_ramp.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id) {
    remove_receiver(list_storehouse, id);
    list_storehouse.remove_by_id(id);
}

template<typename Node>
void Factory::remove_receiver(NodeCollection<Node>& removing_from, ElementID id) {
    auto& to_remove = *(removing_from.find_by_id(id));
    if (removing_from.find_by_id(id) != removing_from.end()) {
        for (auto iter = list_ramp.begin(); iter != list_ramp.end(); iter++) {
            iter->receiver_preferences_.remove_receiver(&to_remove);
        }
        for (auto iter = list_worker.begin(); iter != list_worker.end(); iter++) {
            iter->receiver_preferences_.remove_receiver(&to_remove);
        }
    }
    removing_from.remove_by_id(id);
}

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& color) {
    if (color[sender] == NodeColor::VERIFIED) {
        return true;
    }
    color[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()) { throw std::logic_error("Brak odbiorców"); }

    bool has_sender_at_least_one_receiver = false;
    auto& receiver = sender->receiver_preferences_.get_preferences();
    for (auto iter : receiver) {
        if (iter.first->get_receiver_type() == NodeType::STOREHOUSE) {
            has_sender_at_least_one_receiver = true;
        } else if (iter.first->get_receiver_type() == NodeType::WORKER) {
            IPackageReceiver* receiver_ptr = iter.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (sendrecv_ptr == sender) {
                continue;
            };
            has_sender_at_least_one_receiver = true;
            if (color[sendrecv_ptr] == NodeColor::UNVISITED) {
                has_reachable_storehouse(sendrecv_ptr, color);
            }
        }
    }
    color[sender] = NodeColor::VERIFIED;
    if (has_sender_at_least_one_receiver) {
        return true;
    }
    throw std::logic_error("Błąd");
}

bool Factory::is_consistent() const {
    std::map<const PackageSender*, NodeColor> color;

    for (const auto& element : list_ramp) {
        color[(PackageSender*) &element] = NodeColor::UNVISITED;
    }

    for (const auto& element : list_worker) {
        color[(PackageSender*) &element] = NodeColor::UNVISITED;
    }

    for (const auto& element: list_ramp) {

        try {
            has_reachable_storehouse(&element, color);
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    return true;
}

template
class NodeCollection<Ramp>;

template
class NodeCollection<Worker>;

template
class NodeCollection<Storehouse>;
