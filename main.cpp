
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "DivSales.h"

int main(int argc, char* argv[])
{
    // Select the input file
    std::string filename =
        argc > 1
            ? argv[1]
            : "Corporate_Sales_Quarterly_Test_Data.txt";

    std::ifstream inputFile(filename);

    if (!inputFile)
    {
        std::cerr << "Error opening sales file.\n";
        return 1;
    }

    // Read and validate the number of periods
    int numberOfPeriods;

    if (!(inputFile >> numberOfPeriods) || numberOfPeriods <= 0)
    {
        std::cerr << "Invalid number of sales periods.\n";
        return 1;
    }

    const int NUM_DIVISIONS = 6;

    // Create six separate DivSales objects
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

    // Load and validate all sales values
    for (int division = 0; division < NUM_DIVISIONS; division++)
    {
        for (int period = 0; period < numberOfPeriods; period++)
        {
            if (!(inputFile >> divisions[division][period]) ||
                divisions[division][period] <= 0.0)
            {
                std::cerr << "Invalid or missing sales data.\n";
                return 1;
            }
        }
    }

    // Reject unexpected extra data
    std::string extraValue;

    if (inputFile >> extraValue)
    {
        std::cerr << "Error: Unexpected extra sales data.\n";
        return 1;
    }

    // All file data has been validated
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Corporate Sales Report\n";
    std::cout << "File: " << filename << '\n';
    std::cout << "Number of periods: " << numberOfPeriods << "\n\n";

    // Calculate and display division totals
    for (int division = 0; division < NUM_DIVISIONS; division++)
    {
        double divisionTotal =
            divisions[division].getTotalSales();

        DivSales::addCorporateSales(divisionTotal);

        std::cout << "Division " << division + 1 << " total: $" << divisionTotal << '\n';
    }

    // Display corporate total
    std::cout << "\nCorporate total: $" << DivSales::getCorporateSales() << '\n';

    // Display sales by period
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
