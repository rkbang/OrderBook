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
    Results Cancel(OrderPtrListTypeIterator order_ptr_list_iterator);
    private: 
    Results Buy(OrderPtr order);
    Results Sell(OrderPtr order);
    
    Results Order(OrderPtr order);

    BuySidePriceMap buy_side_price_map_;
    SellSidePriceMap sell_side_price_map_;
    std::unordered_map<Action, ProcessingFunction> action_processing_function_map_;
  };

  class TradeEngine {
    public:
    Results Process(OrderPtr order);
    void AddOrderForTracking(OrderPtrListTypeIterator order_ptr_list_iterator);

    private:
    Results Print() const;
    Results Cancel(OrderPtr order);
    Results Order(OrderPtr order);
    StockTradeEngine& GetStockTradeEngine(OrderPtr order);

    std::unordered_map<Symbol, std::unique_ptr<StockTradeEngine>, SymbolHashFunction> stock_trade_engine_map_;

  };
}