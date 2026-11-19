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