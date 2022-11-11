#include <unordered_map>

#include "trade_engine.h"

namespace order_book {
  constexpr char kBuy = 'B';
  constexpr char kSell = 'S';
  constexpr char kCancel = 'X';

  TradeEngine::TradeEngine() {
    action_processing_function_map_[kBuy] = std::bind(&TradeEngine::Buy, this, std::placeholders::_1);
    action_processing_function_map_[kSell] = std::bind(&TradeEngine::Sell, this, std::placeholders::_1);
    action_processing_function_map_[kCancel] = std::bind(&TradeEngine::Cancel, this, std::placeholders::_1);
  }

  Results TradeEngine::Buy(OrderPtr order) {
    return Results();

  }
  Results TradeEngine::Sell(OrderPtr order) {
    return Results();
  }
  Results TradeEngine::Cancel(OrderPtr order) {
    return Results();
  }

  void TradeEngine::Process(OrderPtr order) {
    auto iter = action_processing_function_map_.find(order->action);
    if (iter != action_processing_function_map_.end()) {
      iter->second(std::move(order));
    }
  }
}