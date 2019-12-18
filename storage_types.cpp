//
// Created by Imperator on 13.12.2019.
//

#include "storage_types.hpp"

void PackageQueue::push(Package&& package) {
    list_.emplace_back(std::move(package));
}

Package PackageQueue::pop() {
    switch (type_) {
        case PackageQueueType::FIFO: {
            Package package(std::move(list_.front()));
            list_.pop_front();
            return package;
        }
        case PackageQueueType::LIFO: {
            Package package(std::move(list_.back()));
            list_.pop_back();
            return package;
        }
    }

}

const size_type PackageQueue::size() {
    return(list_.size());
}

const bool PackageQueue::empty() {
    return(list_.empty());
}

const PackageQueueType PackageQueue::get_queue_type() {
    return(type_);
}

