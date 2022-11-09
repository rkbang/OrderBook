#include <string>
#include <fstream>
#include <iostream>
#include <list>

#include "parser.h"

typedef std::list<std::string> results_t;

class SimpleCross
{
public:
    results_t action(const std::string& line) { 
        std::unique_ptr<order_book::Order> order_ptr = order_parser_.Parse(line.c_str());
        if (order_ptr) {
            order_ptr->Print();
        } else {
            std::cout << "Unable to parse order";
        }
        return(results_t()); 
    }
private:
    order_book::OrderParser order_parser_;
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