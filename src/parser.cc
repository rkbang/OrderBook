#include "parser.h"
#include "allocator.h"

#include <iostream>

namespace order_book {
constexpr char format[] = "%c %u %s %c %hu %lf";

OrderPtr OrderParser::Parse(const char* input) {
  OrderPtr order = Allocator<Order>::instance().allocate();
  double price = 0.0;
  if (sscanf(input, format, &order->action, &order->order_id, order->symbol.data(), &order->side, &order->quantity, &price) <= 0) {
    Allocator<Order>::instance().deallocate(order);
    return nullptr;
  }
  order->normalized_price = price * kNormalizationMultiplier;
  return order;
}
}