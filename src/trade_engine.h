#include <unordered_map>

#include "price_map.h"
#include "types.h"

namespace order_book {
  typedef std::function<Results(OrderPtr order)> ProcessingFunction;
  class TradeEngine {
    public:
    TradeEngine();
    void Process(OrderPtr order);

    private: 
    Results Buy(OrderPtr order);
    Results Sell(OrderPtr order);
    Results Cancel(OrderPtr order);

    PriceMap<BuySideCompareOperator> buy_side_price_map_;
    PriceMap<SellSideCompareOperator> sell_side_price_map_;
    std::unordered_map<Action, ProcessingFunction> action_processing_function_map_;
    std::unordered_map<OrderId, OrderPtrListTypeIterator> order_id_list_ptr_iterator_map_;
  };
}