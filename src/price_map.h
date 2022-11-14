#pragma once
#include <map>
#include <iostream>

#include "types.h"
#include "order_list.h"

namespace order_book {
constexpr char kPartial = 'P';
constexpr char kFull = 'F';
constexpr char kFill[] = "F";

template <class CompareOperator>
class PriceMap {
  public:

    std::size_t Size() {
      return price_map_.size();
    }
    void Add(OrderPtr order) {
      price_map_[order->normalized_price].Add(order);
    }

    void Remove(OrderPtrListTypeIterator iterator) {
      NormalizedPrice normalized_price = (*iterator)->normalized_price;
      price_map_[normalized_price].Remove(iterator);
      if (price_map_[normalized_price].Empty()) {
        price_map_.erase(normalized_price);
      }
    }

  Results ProcessOrder(OrderPtr order) {
    Results results;
    Quantity total_trade_quantity(0);
    CompareOperator compare_op;
    order->Print();
    for (auto price_map_iter(price_map_.begin()); price_map_iter != price_map_.end() && order->quantity > 0;) {
      if(price_map_iter->first == order->normalized_price ||
        compare_op(price_map_iter->first, order->normalized_price)) {
        for(auto iter(price_map_iter->second.begin()); iter != price_map_iter->second.end() && order->quantity > 0;) {
          int trade_quantity = order->quantity > (*iter)->quantity ? (*iter)->quantity : order->quantity;
          order->quantity -= trade_quantity;
          (*iter)->quantity -= trade_quantity;

          if (trade_quantity>0) {
            // "F 10003 IBM 5 100.00000"
            total_trade_quantity += trade_quantity;
            results.push_back(
              std::string(kFill) + " " +
              std::to_string((*iter)->order_id) + " " +
              std::string((*iter)->symbol.bytes) + " " +
              std::to_string(trade_quantity) + " " +
              std::to_string(GetDeNormalizedPrice((*iter)->normalized_price))
              );
          }
          
          if ((*iter)->quantity == 0) {
            price_map_iter->second.Remove(iter++);
          } else {
            ++iter;
          }
        }
      }
      if (price_map_iter->second.Empty()) {
            price_map_.erase(price_map_iter++);
      } else {
          ++price_map_iter;
      }
    }
    if (total_trade_quantity > 0) {
      results.push_front(
              std::string(kFill) + " " +
              std::to_string(order->order_id) + " " +
              std::string(order->symbol.bytes) + " " +
              std::to_string(total_trade_quantity) + " " +
              std::to_string(GetDeNormalizedPrice(order->normalized_price))
              );
    }
    return results;
  }

  Results Print(const std::string& type) const{
    Results results;
    for (auto price_map_iter(price_map_.rbegin()); price_map_iter != price_map_.rend(); ++price_map_iter) {
      for(auto iter(price_map_iter->second.begin()); iter != price_map_iter->second.end(); ++iter) {
        results.push_back(
          "P " +
          std::to_string((*iter)->order_id) + " " +
          std::string((*iter)->symbol.bytes) + " " +
          type + " " +
          std::to_string((*iter)->quantity) + " " +
          std::to_string(GetDeNormalizedPrice((*iter)->normalized_price))
        );
      }
    }
    return results;
  }
  private:
  std::map<NormalizedPrice, OrderList, CompareOperator> price_map_;
};

}