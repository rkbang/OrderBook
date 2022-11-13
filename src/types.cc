#include "types.h"
#include <cstdint>
#include <iostream>

#include <list>
namespace order_book
{
  void Order::Print()
  {
    std::cout << action << " " << order_id << " " << symbol.bytes << " " << side << " " << quantity << " " << normalized_price << std::endl;
  }
}
