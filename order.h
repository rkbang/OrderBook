#include <iostream>
#include <string>

#include "types.h"

namespace order_book
{
    struct Order
    {
        Action action;
        OrderId order_id;
        Symbol symbol;
        Side side;
        Quantity quantity;
        Price price;

        void Print() {
            std::cout << action << " " << order_id << " " << symbol.bytes << " " << side << " " << quantity << " " << price << std::endl;
        }
    };
}