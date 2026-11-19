#include "DivSales.h"
#include <stdexcept>

double DivSales::corporateSales = 0.0;

DivSales::DivSales(int periods)
{
    if (periods <= 0)
    {
        throw std::invalid_argument(
            "Number of periods must be positive"
        );
    }

    numberOfPeriods = periods;
    sales = new double[numberOfPeriods];

    for (int i = 0; i < numberOfPeriods; i++)
    {
        sales[i] = 0.0;
    }
}

DivSales::~DivSales()
{
    delete[] sales;
}

int DivSales::getNumberOfPeriods() const
{
    return numberOfPeriods;
}

double& DivSales::operator[](int index)
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw std::out_of_range("Invalid sales array index");
    }

    return sales[index];
}

const double& DivSales::operator[](int index) const
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw std::out_of_range("Invalid sales array index");
    }

    return sales[index];
}

DivSales::DivSales(const DivSales& other)
{
    numberOfPeriods = other.numberOfPeriods;

    sales = new double[numberOfPeriods];

    for (int i = 0; i < numberOfPeriods; i++)
    {
        sales[i] = other.sales[i];
    }
}

DivSales& DivSales::operator=(const DivSales& other)
{
    // Prevent self-assignment
    if (this == &other)
    {
        return *this;
    }

    // Allocate replacement memory first
    double* newSales = new double[other.numberOfPeriods];

    // Copy the source values
    for (int i = 0; i < other.numberOfPeriods; i++)
    {
        newSales[i] = other.sales[i];
    }

    // Release the old array
    delete[] sales;

    // Take ownership of the new array
    sales = newSales;
    numberOfPeriods = other.numberOfPeriods;

    return *this;
}