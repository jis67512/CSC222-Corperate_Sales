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
std::cout << "\nTEST 5: Copy constructor\n";

DivSales original(4);
original[0] = 125000.00;

DivSales copied(original);

std::cout << "Original: " << original[0] << '\n';
std::cout << "Copy: " << copied[0] << '\n';

copied[0] = 200000.00;

std::cout << "After changing copy:\n";
std::cout << "Original: " << original[0] << '\n';
std::cout << "Copy: " << copied[0] << '\n';

std::cout << "\nTEST 6: Copy assignment\n";

DivSales source(4);
source[0] = 125000.00;

DivSales destination(12);

destination = source;

std::cout << "Destination periods: " << destination.getNumberOfPeriods() << '\n';

std::cout << "Source value: " << source[0] << '\n';
std::cout << "Destination value: " << destination[0] << '\n';

destination[0] = 200000.00;

std::cout << "After changing destination:\n";
std::cout << "Source: " << source[0] << '\n';
std::cout << "Destination: " << destination[0] << '\n';

// Test self-assignment
destination = destination;

std::cout << "After self-assignment: " << destination[0] << '\n';
    return 0;
}