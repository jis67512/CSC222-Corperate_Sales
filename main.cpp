#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "DivSales.h"
#include <fstream>

int main(int argc, char* argv[])
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

std::cout << "\nTEST 7: Corporate Sales file input\n";

std::string filename =
    argc > 1
        ? argv[1]
        : "Corporate_Sales_Quarterly_Test_Data.txt";

std::ifstream inputFile(filename);
std::cout << "Loading file: " << filename << '\n';

if (!inputFile)
{
    std::cerr << "Error opening sales file.\n";
    return 1;
}

int numberOfPeriods;

if (!(inputFile >> numberOfPeriods) || numberOfPeriods <= 0)
{
    std::cerr << "Invalid number of sales periods.\n";
    return 1;
}

std::cout << "Number of periods: " << numberOfPeriods << '\n';

const int NUM_DIVISIONS = 6;

DivSales divisions[NUM_DIVISIONS] =
{
    DivSales(numberOfPeriods),
    DivSales(numberOfPeriods),
    DivSales(numberOfPeriods),
    DivSales(numberOfPeriods),
    DivSales(numberOfPeriods),
    DivSales(numberOfPeriods)
};

DivSales::resetCorporateSales();

std::cout << std::fixed << std::setprecision(2);

// Load and validate the sales values
for (int division = 0; division < NUM_DIVISIONS; division++)
{
    for (int period = 0; period < numberOfPeriods; period++)
    {
        if (!(inputFile >> divisions[division][period]) ||
            divisions[division][period] <= 0.0)
        {
            std::cerr << "Invalid or missing sales data.\n";
            DivSales::resetCorporateSales();
            return 1;
        }
    }
} // Closes the outer division loop

// Check for unexpected extra data
std::string extraValue;

if (inputFile >> extraValue)
{
    std::cerr << "Error: Unexpected extra sales data.\n";
    DivSales::resetCorporateSales();
    return 1;
}

// Now calculate totals after validation succeeds
for (int division = 0; division < NUM_DIVISIONS; division++)
{
    double divisionTotal =
        divisions[division].getTotalSales();

    DivSales::addCorporateSales(divisionTotal);

    std::cout << "Division " << division + 1 << " total: $" << divisionTotal << '\n';
}

// Display the corporate total
std::cout << "Corporate total: $" << DivSales::getCorporateSales() << '\n';

// Display every sales period
std::cout << "\nSales by Period\n";

std::cout << std::left << std::setw(10) << "Period";

for (int d = 0; d < NUM_DIVISIONS; d++)
{
    std::cout << std::right << std::setw(15) << ("Division " + std::to_string(d + 1));
}

std::cout << '\n';

for (int p = 0; p < numberOfPeriods; p++)
{
    std::cout << std::left << std::setw(10) << p + 1;

    for (int d = 0; d < NUM_DIVISIONS; d++)
    {
        std::cout << std::right << std::setw(15) << divisions[d][p];
    }

    std::cout << '\n';
}

return 0;
}