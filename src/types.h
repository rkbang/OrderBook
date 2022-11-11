#pragma once
#include <cstdint>

#include <list>

typedef char Action;
typedef char Side;
typedef uint32_t OrderId;
typedef char* SymbolBytes;
typedef struct Symbol {
    char bytes[6];
} Symbol;
typedef uint16_t Quantity;
typedef double Price;
typedef uint64_t NormalizedPrice;
typedef std::greater<uint64_t> BuySideCompareOperator;
typedef std::less<uint64_t> SellSideCompareOperator;
typedef std::list<std::string> Results;

constexpr uint64_t kNormalizationMultiplier = 100000;

