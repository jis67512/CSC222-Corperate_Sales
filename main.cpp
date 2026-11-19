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
    std::cout << "\nTEST 3: Indexed access\n";

    DivSales division(4);

    std::cout << "Initial value: " << division[0] << '\n';

    division[0] = 125000.00;
    std::cout << "Updated value: " << division[0] << '\n';

    const DivSales& readOnly = division;
    std::cout << "Read-only value: " << readOnly[0] << '\n';

    std::cout << "\nTEST 4: Invalid index\n";

    try
{
    division[-1] = 50000.00;
}
catch (const std::out_of_range& error)
{
    std::cout << "Caught error: " << error.what() << '\n';
}

try
{
    division[4] = 50000.00;
}
catch (const std::out_of_range& error)
{
    std::cout << "Upper-bound error: " << error.what() << '\n';
}
    return 0;
}