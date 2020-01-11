#ifndef NET_SIMULATION_HELPERS_HPP
#define NET_SIMULATION_HELPERS_HPP

#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>

std::random_device rd;
std::mt19937 rng(rd());

double probability_generator() { return std::generate_canonical<double, 10>(rng); }

#endif //NET_SIMULATION_HELPERS_HPP
