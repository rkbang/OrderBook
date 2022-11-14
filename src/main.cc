#include <string>
#include <fstream>
#include <iostream>
#include <list>

#include "parser.h"
#include "trade_engine.h"
#include "allocator.h"

typedef std::list<std::string> results_t;

class SimpleCross
{
public:
    results_t action(const std::string& line) { 
        order_book::OrderPtr order_ptr = order_parser_.Parse(line.c_str());
        if (order_ptr) {
            return trade_engine_.Process(order_ptr);
        } 
        results_t results;
        results.push_back("E Unable to process: " + line);
        return results;
    }
private:
    order_book::OrderParser order_parser_;
    order_book::TradeEngine trade_engine_;
};

int main(int argc, char **argv)
{
    SimpleCross scross;
    std::string line;
    std::ifstream actions("actions.txt", std::ios::in);
    while (std::getline(actions, line))
    {
        results_t results = scross.action(line);
        for (results_t::const_iterator it=results.begin(); it!=results.end(); ++it)
        {
            std::cout << *it << std::endl;
        }
    }
    return 0;
}