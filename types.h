#include <cstdint>

typedef char Action;
typedef char Side;
typedef uint32_t OrderId;
typedef struct Symbol {
    char bytes[6];
} Symbol;
typedef uint16_t Quantity;
typedef double Price;
typedef uint64_t NormalizedPrice;