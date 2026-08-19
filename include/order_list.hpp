#pragma once
#include <algorithm>
#include <vector>
#include "order.hpp"

// A simple owning container of resting orders. The vector OWNS the orders:
// they live inside it, and are destroyed when the vector is.
class OrderList {
public:
    void add(const Order& o) {
        orders_.push_back(o);   // copies the order INTO the vector
    }

    std::size_t size() const {
        return orders_.size();
    }

    // Remove every order with the given id. The erase-remove idiom shuffles
    // the survivors to the front, then trims the tail in one shot.
    void cancel(std::uint64_t id) {
        auto new_end = std::remove_if(
            orders_.begin(), orders_.end(),
            [id](const Order& o) { return o.id == id; });
        orders_.erase(new_end, orders_.end());
    }

    const std::vector<Order>& view() const {
        return orders_;
    }

private:
    std::vector<Order> orders_;
};
