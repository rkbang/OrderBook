#include <unordered_map>

#include "order_list.h"
#include "types.h"

namespace order_book {
  typedef std::unordered_map<OrderId, OrderPtrListTypeIterator> OrderIdPtrListIteratorMap;
  struct OrderRegistry {
    static OrderRegistry& instance();
    void RemoveOrder(OrderPtrListTypeIterator order_ptr_list_iterator);
    bool OrderExists(OrderId order_id);
    void AddOrderForTracking(OrderPtrListTypeIterator order_ptr_list_iterator);
    OrderIdPtrListIteratorMap& GetOrderRegistryMap();

    private:
    OrderIdPtrListIteratorMap order_id_list_ptr_iterator_map_;
  };
}