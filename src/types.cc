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

  void Order::Reset(Action action, OrderId order_id, const Symbol& symbol, Side side, Quantity quantity, double price) {
    this->action = action;
    this->order_id = order_id;
    this->symbol = symbol;
    this->side = side;
    this->quantity = quantity;
    this->normalized_price = price * kNormalizationMultiplier;
  }
}
