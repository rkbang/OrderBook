#include "parser.h"

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

constexpr char format[] = "%c %u %s %c %u %lf";

std::unique_ptr<Order> OrderParser::Parse(const char* input) {
  std::cout << input << std::endl;
  std::unique_ptr<Order> order = std::make_unique<Order>();
  if (sscanf(input, format, &order->action, &order->order_id, &order->symbol, &order->side, &order->quantity, &order->price) <= 0) {
    order.reset();
  }
  return order;
}
}