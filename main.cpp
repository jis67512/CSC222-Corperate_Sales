#include <iostream>
#include <stdexcept>
#include "DivSales.h"

int main()
{
    std::cout << "TEST 1: Valid constructor\n";

    {
        DivSales quarterly(4);
        std::cout << "Created division with 4 periods.\n";
    }

    std::cout << "TEST 2: Invalid constructor\n";

    try
    {
        DivSales invalid(0);
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Caught error: " << error.what() << '\n';
    }

    return 0;
}