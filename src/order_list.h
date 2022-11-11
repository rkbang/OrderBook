#include <list>

#include "order.h"
#include "types.h"

namespace order_book {
  typedef std::list<OrderPtr> OrderPtrListType;
  typedef OrderPtrListType::iterator OrderPtrListTypeIterator;
  class OrderList {
    public:
    OrderPtrListTypeIterator Add(OrderPtr order);
    void Remove(const OrderPtrListTypeIterator& iterator);

    private:
    OrderPtrListType order_list_;
  };
}