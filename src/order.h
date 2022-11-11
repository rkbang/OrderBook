#include <iostream>
#pragma once
#include <string>
#include <memory>

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
        NormalizedPrice normalized_price;

        void Print() {
            std::cout << action << " " << order_id << " " << symbol.bytes << " " << side << " " << quantity << " " << normalized_price << std::endl;
        }
    };
    typedef std::shared_ptr<Order> OrderPtr; 
}