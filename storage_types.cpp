//
// Created by Imperator on 13.12.2019.
//

#include "storage_types.hpp"

const void PackageQueue::push(Package&& package) {
    list_.emplace_back(std::move(package));
}

Package&& PackageQueue::pop() {

}

PackageQueue::PackageQueue(const PackageQueueType type) {
    switch (type) {
        case PackageQueueType::FIFO:
                type_ = type;

            break;

        case PackageQueueType::LIFO:
                type_ = type;

            break;
    }

}