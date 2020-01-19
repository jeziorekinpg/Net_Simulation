//
// Created by barte on 19.01.2020.
//

#ifndef NETSIM_SIMULATION_HPP
#define NETSIM_SIMULATION_HPP

#include "factory.hpp"

void simulate(Factory&, TimeOffset, std::function<void (Factory&, Time)>);

#endif //NETSIM_SIMULATION_HPP
