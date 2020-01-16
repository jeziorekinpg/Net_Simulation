#include "factory.hpp"
#include <map>

bool Factory::is_consistent() const {
    std::map<PackageSender*, NodeColor> color;

    for(const auto& element: list_ramp) {
        color[(PackageSender *) &element] = NodeColor::UNVISITED;
    }

    for(const auto& element: list_worker) {
        color[(PackageSender *) &element] = NodeColor::UNVISITED;
    }

    //for(const auto& element: list_ramp) {

     //   try {
     //       has_reachable_storehouse(&element, color)
     //       return true;
     //   }
     //   catch(NoReceiverException& noReceiversException) {
     //       return false;
      //  }
    //}
    return true;
}

void Factory::do_deliveries(Time t) {
  for(auto iter = list_ramp.begin(); iter <= list_ramp.end(); iter++){
    iter->deliver_goods(t);
  }
}

void Factory::do_work(Time t) {
  for(auto iter = list_worker.begin(); iter <= list_worker.end(); iter++){
    iter->do_work(t);
  }
}

void Factory::do_package_passing() {
  for(auto iter = list_ramp.begin(); iter <= list_ramp.end(); iter++){
    iter->send_package();
  }
  for(auto iter = list_worker.begin(); iter <= list_worker.end(); iter++){
    iter->send_package();
  }
}
