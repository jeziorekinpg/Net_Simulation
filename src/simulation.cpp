//
// Created by barte on 19.01.2020.
//

#include "simulation.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void(Factory&, Time)> rf) {
    for(TimeOffset i = 1; i <= d; i++) {
        f.do_deliveries(i);
        f.do_package_passing();
        f.do_work(i);

    }

}
