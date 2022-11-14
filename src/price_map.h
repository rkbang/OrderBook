#pragma once
#include <map>
#include <iostream>

#include "types.h"
#include "order_list.h"

namespace order_book
{
  constexpr char kFill[] = "F";

  template <class CompareOperator>
  class PriceMap
  {
  public:
    typedef std::map<NormalizedPrice, OrderList, CompareOperator> PriceOrderListMap;
    typedef typename PriceOrderListMap::const_iterator PriceOrderListMapConstIterator;
    std::size_t Size()
    {
      return price_map_.size();
    }
    void Add(OrderPtr order)
    {
      price_map_[order->normalized_price].Add(order);
    }

    void Remove(OrderPtrListTypeIterator iterator)
    {
      NormalizedPrice normalized_price = (*iterator)->normalized_price;
      price_map_[normalized_price].Remove(iterator);
      if (price_map_[normalized_price].Empty())
      {
        price_map_.erase(normalized_price);
      }
    }

    Results ProcessOrder(OrderPtr order)
    {
      Results results;
      Quantity total_trade_quantity(0);
      CompareOperator compare_op;
      for (auto price_map_iter(price_map_.begin()); price_map_iter != price_map_.end() && order->quantity > 0;)
      {
        if (price_map_iter->first == order->normalized_price ||
            compare_op(price_map_iter->first, order->normalized_price))
        {
          for (auto iter(price_map_iter->second.begin()); iter != price_map_iter->second.end() && order->quantity > 0;)
          {
            int trade_quantity = order->quantity > (*iter)->quantity ? (*iter)->quantity : order->quantity;
            order->quantity -= trade_quantity;
            (*iter)->quantity -= trade_quantity;

            if (trade_quantity > 0)
            {
              total_trade_quantity += trade_quantity;
              results.push_back(FormulateResult((*iter)->order_id, (*iter)->symbol, trade_quantity, (*iter)->normalized_price));
            }

            if ((*iter)->quantity == 0)
            {
              price_map_iter->second.Remove(iter++);
            }
            else
            {
              ++iter;
            }
          }
        }
        if (price_map_iter->second.Empty())
        {
          price_map_.erase(price_map_iter++);
        }
        else
        {
          ++price_map_iter;
        }
      }
      if (total_trade_quantity > 0)
      {
        results.push_front(FormulateResult(order->order_id, order->symbol, total_trade_quantity, order->normalized_price));
      }
      return results;
    }

    Results Print(const std::string &type) const
    {
      return InternalPrint(type, price_map_.begin(), price_map_.end());
    }

    Results ReversePrint(const std::string &type) const
    {
      return InternalPrint(type, price_map_.rbegin(), price_map_.rend());
    }

  private:
    const std::string FormulateResult(OrderId order_id, const Symbol& symbol, Quantity quantity, NormalizedPrice price)
    {
      return std::string(kFill) + " " +
             std::to_string(order_id) + " " +
             std::string(symbol.data()) + " " +
             std::to_string(quantity) + " " +
             std::to_string(GetDeNormalizedPrice(price));
    }


    template <class Iterator>
    Results InternalPrint(const std::string &type, Iterator begin, Iterator end) const
    {
      Results results;
      for (auto price_map_iter(begin); price_map_iter != end; ++price_map_iter)
      {
        for (auto iter(price_map_iter->second.begin()); iter != price_map_iter->second.end(); ++iter)
        {
          results.push_back(
              "P " +
              std::to_string((*iter)->order_id) + " " +
              std::string((*iter)->symbol.data()) + " " +
              type + " " +
              std::to_string((*iter)->quantity) + " " +
              std::to_string(GetDeNormalizedPrice((*iter)->normalized_price)));
        }
      }
      return results;
    }

    PriceOrderListMap price_map_;
  };

}