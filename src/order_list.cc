#include "order_list.h"

namespace order_book {
  OrderPtrListTypeIterator OrderList::Add(OrderPtr order) {
    order_list_.push_back(std::move(order));
    return --(order_list_.end());
  }
  void OrderList::Remove(const OrderPtrListTypeIterator& iterator) {
    order_list_.erase(iterator);
  }
}