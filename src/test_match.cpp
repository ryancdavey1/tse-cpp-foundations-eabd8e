#include <cassert>
#include <iostream>
#include "match.hpp"

// A buy that crosses a cheaper resting sell should produce a trade at the
// resting (sell) price, for the smaller quantity.
static void test_buy_crosses_sell() {
    Order buy{1, Side::Buy, 101.0, 50};
    Order sell{2, Side::Sell, 100.0, 30};
    auto trade = match_one(buy, sell);
    assert(trade.has_value());
    assert(*trade == Trade{1, 2, 100.0, 30});
}

// A buy priced below the resting sell does not cross: no trade.
static void test_no_cross() {
    Order buy{3, Side::Buy, 99.0, 10};
    Order sell{4, Side::Sell, 100.0, 10};
    assert(!match_one(buy, sell).has_value());
}

// Two buys never trade with each other.
static void test_same_side() {
    Order a{5, Side::Buy, 100.0, 10};
    Order b{6, Side::Buy, 100.0, 10};
    assert(!match_one(a, b).has_value());
}

int main() {
    test_buy_crosses_sell();
    test_no_cross();
    test_same_side();
    std::cout << "all match tests passed\n";
    return 0;
}
