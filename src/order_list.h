#pragma once
#include <list>

#include "types.h"

namespace order_book {
  typedef std::list<OrderPtr> OrderPtrListType;
  typedef OrderPtrListType::iterator OrderPtrListTypeIterator;
  typedef OrderPtrListType::const_iterator OrderPtrListTypeConstIterator;
  class OrderList {
    public:
    OrderPtrListTypeIterator Add(OrderPtr order);
    void Remove(OrderPtrListTypeIterator iterator);
    bool Empty();
    OrderPtrListTypeIterator begin();
		OrderPtrListTypeIterator end();
    OrderPtrListTypeConstIterator begin() const;
		OrderPtrListTypeConstIterator end() const;

    private:
    OrderPtrListType order_list_;
  };
}