#include "parser.h"
#include "allocator.h"

#include <iostream>

namespace order_book {
/*
Inputs:
    A string of space separated values representing an action.  The number of
    values is determined by the action to be performed and have the following
    format:

    ACTION [OID [SYMBOL SIDE QTY PX]]

    ACTION: single character value with the following definitions
    O - place order, requires OID, SYMBOL, SIDE, QTY, PX
    X - cancel order, requires OID
    P - print sorted book (see example below)

    OID: positive 32-bit integer value which must be unique for all orders

    SYMBOL: alpha-numeric string value. Maximum length of 8.

    SIDE: single character value with the following definitions
    B - buy
    S - sell

    QTY: positive 16-bit integer value

    PX: positive double precision value (7.5 format
*/

constexpr char format[] = "%c %u %s %c %hu %lf";

OrderPtr OrderParser::Parse(const char* input) {
  OrderPtr order = Allocator<Order>::instance().allocate();
  double price = 0.0;
  if (sscanf(input, format, &order->action, &order->order_id, &order->symbol.bytes, &order->side, &order->quantity, &price) <= 0) {
    Allocator<Order>::instance().deallocate(order);
    return nullptr;
  }
  order->normalized_price = price * kNormalizationMultiplier;
  return order;
}
}