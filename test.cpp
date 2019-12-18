//
// Created by barte on 18.12.2019.
//
#include <iostream>
#include "storage_types.hpp"
#include "package.hpp"

int main(){
    Package *p1 = new Package();
    Package *p2 = new Package();
    Package *p3 = new Package();


    std::cout << (*p1).get_id() << "\n";
    std::cout << (*p2).get_id() << "\n";
    std::cout << (*p3).get_id() << "\n";
    delete(p2);
    delete(p1);
    Package p5;
    std::cout << p5.get_id() << "\n";
    Package *p4 = new Package();


    std::cout << (*p4).get_id() << "\n";
    Package *p6 = new Package();


    std::cout << (*p6).get_id() << "\n";
    return 1;
}