#pragma once
#include <cstdint>

#include <list>
#include <vector>
namespace order_book
{
    typedef char Action;
    typedef char Side;
    typedef uint32_t OrderId;
    typedef char *SymbolBytes;
    typedef struct Symbol
    {
        char bytes[6];
    } Symbol;
    typedef uint16_t Quantity;
    typedef double Price;
    typedef uint64_t NormalizedPrice;
    typedef std::greater<uint64_t> BuySideCompareOperator;
    typedef std::less<uint64_t> SellSideCompareOperator;
    typedef std::list<std::string> Results;
    constexpr uint64_t kNormalizationMultiplier = 100000;


    struct Order
    {
        Action action;
        OrderId order_id;
        Symbol symbol;
        Side side;
        Quantity quantity;
        NormalizedPrice normalized_price;

        void Print();
    };

    struct Trade
    {
        Action action;
        OrderId order_id;
        Quantity quantity;
        NormalizedPrice normalized_price;
    };

    typedef std::vector<Trade> Trades;
    typedef Order* OrderPtr;
}
