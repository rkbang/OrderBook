#include <map>

#include "types.h"
#include "order_list.h"

namespace order_book {

template <class CompareOperator>
class PriceMap {
  public:
    OrderPtrListTypeIterator Add(OrderPtr order) {
      return price_map_[order->normalized_price].Add(order);
    }

    void Remove(OrderPtrListTypeIterator iterator) {
      NormalizedPrice normalized_price = iterator->get()->normalized_price;
      price_map_[normalized_price].Remove(iterator);
      if (price_map_[normalized_price].Empty()) {
        price_map_.erase(normalized_price);
      }
    }
  private:
  std::map<NormalizedPrice, OrderList, CompareOperator> price_map_;
};

}