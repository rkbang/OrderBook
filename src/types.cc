#include "types.h"
#include <cstdint>
#include <iostream>

#include <list>
namespace order_book
{
  void Order::Print() const
  {
    std::cout << action << " " << order_id << " " << symbol.data() << " " << side << " " << quantity << " " << normalized_price << std::endl;
  }
}
