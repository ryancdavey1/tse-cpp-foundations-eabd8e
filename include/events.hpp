#pragma once
#include <cstdint>
#include <vector>
#include "order.hpp"

// The kind of thing that happened on the market.
enum class EventType { NewOrder, Cancel, Trade };

// A market event composes a type with the data it carries.
struct MarketEvent {
    EventType type;
    std::uint64_t order_id;
    double price;
    std::uint32_t quantity;
};

// std::vector is a growable, contiguous array — cache-friendly and the
// default container for a sequence of events.
inline double total_traded_volume(const std::vector<MarketEvent>& events) {
    double volume = 0.0;
    for (const MarketEvent& e : events) {          // range-based for, by const ref
        if (e.type == EventType::Trade) {
            volume += e.price * static_cast<double>(e.quantity);
        }
    }
    return volume;
}
