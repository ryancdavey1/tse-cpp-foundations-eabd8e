#pragma once
#include "order.hpp"

// Pass by VALUE: `o` is a full copy of the caller's Order.
inline double notional_by_value(Order o) {
    return o.notional();
}

// Pass by CONST REFERENCE: `o` is an alias to the caller's Order, with a
// read-only promise. No copy is made.
inline double notional_by_ref(const Order& o) {
    return o.notional();
}

// A non-const reference lets us modify the caller's object in place.
inline void apply_fill(Order& o, std::uint32_t filled) {
    o.quantity -= filled;
}
