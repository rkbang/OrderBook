#include "order_list.h"
#include "allocator.h"

namespace order_book {
  OrderPtrListTypeIterator OrderList::Add(OrderPtr order) {
    order_list_.push_back(std::move(order));
    return --(order_list_.end());
  }
  void OrderList::Remove(OrderPtrListTypeIterator iterator) {
    Allocator<Order>::instance().deallocate(*iterator);
    order_list_.erase(iterator);
  }

  bool OrderList::Empty() {
    return order_list_.empty();
  }

  OrderPtrListTypeIterator OrderList::begin() {
    return order_list_.begin();
  }
	OrderPtrListTypeIterator OrderList::end() {
    return order_list_.end();
  }

  OrderPtrListTypeConstIterator OrderList::begin() const{
    return order_list_.begin();
  }
	OrderPtrListTypeConstIterator OrderList::end() const{
    return order_list_.end();
  }
}