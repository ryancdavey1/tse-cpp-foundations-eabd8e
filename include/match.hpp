#pragma once
#include <algorithm>
#include <optional>
#include "order.hpp"
#include "trade.hpp"

// Decide whether an incoming order crosses a resting order on the other side.
// A buy crosses a sell when the buyer is willing to pay at least the ask.
inline bool crosses(const Order& incoming, const Order& resting) {
    if (incoming.side == resting.side) return false;   // same side never trades
    if (incoming.side == Side::Buy) return incoming.price >= resting.price;
    return incoming.price <= resting.price;            // incoming is a Sell
}

// If they cross, produce the Trade. std::optional models "maybe a trade":
// either there is one, or there isn't, with no sentinel values.
inline std::optional<Trade> match_one(const Order& incoming, const Order& resting) {
    if (!crosses(incoming, resting)) return std::nullopt;
    std::uint32_t qty = std::min(incoming.quantity, resting.quantity);
    std::uint64_t buy_id  = incoming.side == Side::Buy ? incoming.id : resting.id;
    std::uint64_t sell_id = incoming.side == Side::Buy ? resting.id  : incoming.id;
    return Trade{buy_id, sell_id, resting.price, qty};
}
