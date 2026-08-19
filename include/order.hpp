#pragma once
#include <cstdint>
#include <string>

// An enum class names a fixed set of values — and unlike a plain enum,
// the names are scoped (Side::Buy) and won't implicitly convert to int.
enum class Side { Buy, Sell };

// A struct groups related fields. In C++ a struct is a VALUE: copying it
// copies every field. There is no hidden pointer or garbage collector.
struct Order {
    std::uint64_t id;
    Side side;
    double price;
    std::uint32_t quantity;

    // A const member function promises not to modify the object. The
    // trailing `const` lets you call it on a const Order.
    double notional() const {
        return price * static_cast<double>(quantity);
    }
};
