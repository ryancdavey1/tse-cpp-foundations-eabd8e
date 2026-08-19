#pragma once
#include <cstdint>
#include "order.hpp"

// A Trade is the result of two orders matching: a buyer and a seller agree
// on a price and a quantity. Like Order, it is a plain value.
struct Trade {
    std::uint64_t buy_id = 0;
    std::uint64_t sell_id = 0;
    double price = 0.0;
    std::uint32_t quantity = 0;

    // The cash that changed hands in this trade.
    double value() const {
        return price * static_cast<double>(quantity);
    }
};

// Two trades are equal when every field matches. We compare values, not
// addresses — that is what "value equality" means.
inline bool operator==(const Trade& a, const Trade& b) {
    return a.buy_id == b.buy_id
        && a.sell_id == b.sell_id
        && a.price == b.price
        && a.quantity == b.quantity;
}
