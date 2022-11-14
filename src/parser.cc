#include "parser.h"
#include "allocator.h"

#include <iostream>

namespace order_book {
constexpr char format[] = "%c %u %s %c %hu %lf";

OrderPtr OrderParser::Parse(const char* input) {
  
  Action action = '\0';
  Side side = '\0';
  OrderId order_id = 0;
  Quantity quantity = 0;
  double price = 0.0;
  Symbol symbol = {'\0'};

  if (sscanf(input, format, &action, &order_id, symbol.data(), &side, &quantity, &price) <= 0) {
    return nullptr;
  }
  OrderPtr order = Allocator<Order>::instance().allocate();
  order->Reset(action, order_id, symbol, side, quantity, price);
  return order;
}
}