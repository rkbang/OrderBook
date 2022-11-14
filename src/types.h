#pragma once
#include <cstdint>
#include <iostream>

#include <list>
#include <vector>
#include <array>
namespace order_book
{
    typedef char Action;
    typedef char Side;
    typedef uint32_t OrderId;
    typedef uint16_t Quantity;
    typedef double Price;
    typedef uint64_t NormalizedPrice;
    typedef std::greater<uint64_t> BuySideCompareOperator;
    typedef std::less<uint64_t> SellSideCompareOperator;
    typedef std::list<std::string> Results;
    constexpr uint64_t kNormalizationMultiplier = 100000;

    constexpr double GetDeNormalizedPrice(double price)
    {
        return price / kNormalizationMultiplier;
    }

    typedef std::array<char, 6> Symbol;

    struct SymbolHashFunction
    {
    public:
        size_t operator()(Symbol symbol) const
        {
            size_t result = 0;
            const size_t prime = 31;
            for (size_t i = 0; i < 6 && symbol[i]!= '\0' && symbol[i] != ' '; ++i) {
                result = symbol[i] + (result * prime);
            }
            return result;
        }
    };

    struct __attribute__ ((__packed__)) Order
    {
        Action action;
        OrderId order_id;
        Symbol symbol;
        Side side;
        Quantity quantity;
        NormalizedPrice normalized_price;
        void Print() const;
        void Reset(Action action, OrderId order_id, const Symbol& symbol, Side side, Quantity quantity, double price);

    } __attribute__ ((aligned));

    typedef Order* OrderPtr;
}
