#include <string>
#include <unordered_map>

#include "trade_engine.h"

namespace order_book {
  constexpr char kBuy = 'B';
  constexpr char kSell = 'S';
  constexpr char kCancel = 'X';
  constexpr char kPrint = 'P';
  constexpr char kOrder = 'O';
  constexpr char kBuyStr[] = "B";
  constexpr char kSellStr[] = "B";

  StockTradeEngine::StockTradeEngine() {
    action_processing_function_map_[kBuy] = std::bind(&StockTradeEngine::Buy, this, std::placeholders::_1);
    action_processing_function_map_[kSell] = std::bind(&StockTradeEngine::Sell, this, std::placeholders::_1);
    action_processing_function_map_[kCancel] = std::bind(&StockTradeEngine::Cancel, this, std::placeholders::_1);
    action_processing_function_map_[kOrder] = std::bind(&StockTradeEngine::Order, this, std::placeholders::_1);
  }


  Results StockTradeEngine::Buy(OrderPtr order) {
    std::cout << "BuyMapSize " << buy_side_price_map_.Size() 
    << " SellMapSize " << sell_side_price_map_.Size() << std::endl;
    Results results = sell_side_price_map_.ProcessOrder(order);
    if (order->quantity > 0) {
      buy_side_price_map_.Add(order);
      std::cout << "Adding Buy Order " << buy_side_price_map_.Size()<< std::endl;
    }
    std::cout << "Buy" << std::endl;
    return results;
  }
  Results StockTradeEngine::Sell(OrderPtr order) {
    std::cout << "BuyMapSize " << buy_side_price_map_.Size() 
    << " SellMapSize " << sell_side_price_map_.Size() << std::endl;
    Results results = buy_side_price_map_.ProcessOrder(order);
    if (order->quantity > 0) {
      sell_side_price_map_.Add(order);
      std::cout << "Adding Sell Order" << sell_side_price_map_.Size()<< std::endl;
    }
    std::cout << "Sell" << std::endl;
    return results;
  }
  Results StockTradeEngine::Cancel(OrderPtr order) {
    return Results();
  }

  Results StockTradeEngine::Print() const {
    Results results;
    results.merge(sell_side_price_map_.Print(kSellStr));
    results.merge(sell_side_price_map_.Print(kBuyStr)); 
    return results;
  }

  Results StockTradeEngine::Order(OrderPtr order) {
    auto iter = action_processing_function_map_.find(order->side);
    if (iter != action_processing_function_map_.end()) {
      return iter->second(order);
    }
    return Results();
  }

  Results StockTradeEngine::Process(OrderPtr order) {
    std::cout << "StockTradeEngine::Process " << order->action << std::endl;
    auto iter = action_processing_function_map_.find(order->action);
    if (iter != action_processing_function_map_.end()) {
      std::cout << "StockTradeEngine::Process Found" << std::endl;
      return iter->second(order);
    }
    return Results();
  }

  Results TradeEngine::Process(OrderPtr order) {
    std::cout << "TradeEngine::Process" << std::endl;
    if (order->action == kCancel) {
      auto order_id_list_ptr_iterator_map_iterator = order_id_list_ptr_iterator_map_.find(order->order_id);
      if (order_id_list_ptr_iterator_map_iterator == order_id_list_ptr_iterator_map_.end()) {
        Results results;
        results.push_back("E Invalid Order Id " +  std::to_string(order->order_id));
        return results;
      }
      OrderPtrListTypeIterator iter = order_id_list_ptr_iterator_map_iterator->second;
      return stock_trade_engine_map_[(*iter)->symbol.bytes].Process(order);
    }
    if (order->action == kPrint) {
      return Print();
    }
    return stock_trade_engine_map_[order->symbol.bytes].Process(order);
  }

  Results TradeEngine::Print() const{
    Results results;
    for(auto iter(stock_trade_engine_map_.begin());
        iter != stock_trade_engine_map_.end();
        ++iter) {
      results.merge(iter->second.Print());
    }
    return results;
  }
}