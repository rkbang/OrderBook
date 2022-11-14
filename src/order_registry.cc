#include "order_registry.h"

namespace order_book {

  OrderRegistry& OrderRegistry::instance()
  {
    static OrderRegistry instance;
    return instance;
  }

  bool OrderRegistry::OrderExists(OrderId order_id) {
    return order_id_list_ptr_iterator_map_.find(order_id) != order_id_list_ptr_iterator_map_.end();
  }

  void OrderRegistry::RemoveOrder(OrderPtrListTypeIterator order_ptr_list_iterator) {
    order_id_list_ptr_iterator_map_.erase((*order_ptr_list_iterator)->order_id);
  }
  void OrderRegistry::AddOrderForTracking(OrderPtrListTypeIterator order_ptr_list_iterator) {
    order_id_list_ptr_iterator_map_[(*order_ptr_list_iterator)->order_id] = order_ptr_list_iterator;
  }

  OrderIdPtrListIteratorMap& OrderRegistry::GetOrderRegistryMap() {
    return order_id_list_ptr_iterator_map_;
  }
}