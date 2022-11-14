#include "order_list.h"
#include "allocator.h"
#include "order_registry.h"

namespace order_book {
  OrderPtrListTypeIterator OrderList::Add(OrderPtr order) {
    order_list_.push_back(order);
    OrderPtrListTypeIterator order_ptr_list_iterator = --(order_list_.end());
    OrderRegistry::instance().AddOrderForTracking(order_ptr_list_iterator);
    return order_ptr_list_iterator;
  }
  void OrderList::Remove(OrderPtrListTypeIterator iterator) {
    OrderRegistry::instance().RemoveOrder(iterator);
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