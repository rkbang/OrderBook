#include <unordered_map>

#include "price_map.h"
#include "types.h"

namespace order_book {
  typedef std::function<Results(OrderPtr order)> ProcessingFunction;
  typedef PriceMap<BuySideCompareOperator> BuySidePriceMap;
  typedef PriceMap<SellSideCompareOperator> SellSidePriceMap;
  class StockTradeEngine {
    public:
    StockTradeEngine();
    Results Process(OrderPtr order);
    Results Print() const;

    private: 
    Results Buy(OrderPtr order);
    Results Sell(OrderPtr order);
    Results Cancel(OrderPtr order);
    Results Order(OrderPtr order);

    BuySidePriceMap buy_side_price_map_;
    SellSidePriceMap sell_side_price_map_;
    std::unordered_map<Action, ProcessingFunction> action_processing_function_map_;
  };

  class TradeEngine {
    public:
    Results Process(OrderPtr order);

    private:
    Results Print() const;

    std::unordered_map<std::string, StockTradeEngine> stock_trade_engine_map_;
    std::unordered_map<OrderId, OrderPtrListTypeIterator> order_id_list_ptr_iterator_map_;
  };
}