//
// Created by Imperator on 13.12.2019.
//

#include "storage_types.hpp"

void PackageQueue::push(Package&& package) {
    list_.emplace_back(std::move(package));
}

Package PackageQueue::pop() {
    Package package;
    switch (type_) {
        case PackageQueueType::FIFO: {
            package = std::move(list_.front());
            list_.pop_front();
            break;
        }
        case PackageQueueType::LIFO: {
            package = std::move(list_.back());
            list_.pop_back();
            break;
        }
    }
    return package;
}

size_type PackageQueue::size() const {
    return(list_.size());
}

bool PackageQueue::empty() const {
    return(list_.empty());
}

PackageQueueType PackageQueue::get_queue_type() const {
    return(type_);
}
