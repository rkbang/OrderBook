#include <string>
#include <unordered_map>

#include "trade_engine.h"
#include "order_registry.h"

namespace order_book {
  constexpr char kBuy = 'B';
  constexpr char kSell = 'S';
  constexpr char kCancel = 'X';
  constexpr char kPrint = 'P';
  constexpr char kOrder = 'O';
  constexpr char kBuyStr[] = "B";
  constexpr char kSellStr[] = "S";

  StockTradeEngine::StockTradeEngine()
  {
    action_processing_function_map_[kBuy] = std::bind(&StockTradeEngine::Buy, this, std::placeholders::_1);
    action_processing_function_map_[kSell] = std::bind(&StockTradeEngine::Sell, this, std::placeholders::_1);
    action_processing_function_map_[kOrder] = std::bind(&StockTradeEngine::Order, this, std::placeholders::_1);
  }


  Results StockTradeEngine::Buy(OrderPtr order) {
    Results results = sell_side_price_map_.ProcessOrder(order);
    if (order->quantity > 0) {
      buy_side_price_map_.Add(order);
    }
    return results;
  }

  Results StockTradeEngine::Sell(OrderPtr order) {
    Results results = buy_side_price_map_.ProcessOrder(order);
    if (order->quantity > 0) {
      sell_side_price_map_.Add(order);
    }
    return results;
  }
  Results StockTradeEngine::Cancel(OrderPtrListTypeIterator order_ptr_list_iterator) {
    switch((*order_ptr_list_iterator)->side) {
      case kBuy:
      buy_side_price_map_.Remove(order_ptr_list_iterator);
      break;
      case kSell:
      sell_side_price_map_.Remove(order_ptr_list_iterator);
      break;
    }
    return Results();
  }

  Results StockTradeEngine::Print() const {
    Results results;
    results.splice(results.end(), sell_side_price_map_.ReversePrint(kSellStr));
    results.splice(results.end(), buy_side_price_map_.Print(kBuyStr)); 
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
    auto iter = action_processing_function_map_.find(order->action);
    if (iter != action_processing_function_map_.end()) {
      return iter->second(order);
    }
    return Results();
  }

  StockTradeEngine& TradeEngine::GetStockTradeEngine(OrderPtr order) {

    auto symbol_trade_engine_iter = stock_trade_engine_map_.find(order->symbol);
    if (symbol_trade_engine_iter == stock_trade_engine_map_.end()) {
      symbol_trade_engine_iter = stock_trade_engine_map_.emplace(order->symbol, 
      std::make_unique<StockTradeEngine>()).first;
    }
    return *(symbol_trade_engine_iter->second);
  }

  Results TradeEngine::Cancel(OrderPtr order) { 
    Results results;
    auto& order_id_list_ptr_iterator_map = OrderRegistry::instance().GetOrderRegistryMap();
    auto order_id_list_ptr_iterator_map_iterator = order_id_list_ptr_iterator_map.find(order->order_id);
    if (order_id_list_ptr_iterator_map_iterator == order_id_list_ptr_iterator_map.end()) {
      results.push_back("E Invalid Order Id " +  std::to_string(order->order_id));
      return results;
    } else {
      results.push_back("X " +  std::to_string(order->order_id));
      GetStockTradeEngine(*(order_id_list_ptr_iterator_map_iterator->second)).Cancel(order_id_list_ptr_iterator_map_iterator->second);
      OrderRegistry::instance().RemoveOrder(order_id_list_ptr_iterator_map_iterator->second);
    }
    return results;
  }

  Results TradeEngine::Order(OrderPtr order) { 
    Results results;
    if(OrderRegistry::instance().OrderExists(order->order_id)) {
      results.push_back("E " + std::to_string(order->order_id) + " Duplicate order id");
      return results;
    }
    StockTradeEngine& stock_trade_engine(GetStockTradeEngine(order));
    results.splice(results.end(), stock_trade_engine.Process(order));
    return results;
  }

  Results TradeEngine::Process(OrderPtr order) {
    Results results;
    switch(order->action) {
      case kPrint:
      return Print();
      case kCancel:
      return Cancel(order);
      case kOrder:
      return Order(order);
      default:
        results.push_back("E Invalid action " +  std::string(1, order->action));
    }
    return results;
  }

  Results TradeEngine::Print() const{
    Results results;
    for(auto iter(stock_trade_engine_map_.begin());
        iter != stock_trade_engine_map_.end();
        ++iter) {
      results.splice(results.end(), iter->second->Print());
    }
    return results;
  }
}