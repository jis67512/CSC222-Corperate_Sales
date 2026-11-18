#ifndef DIVSALES_H
#define DIVSALES_H

class DivSales
{
private:
    double* sales;
    int numberOfPeriods;
    static double corporateSales;

public:
    DivSales(int periods);
    ~DivSales();

    DivSales(const DivSales& other);
    DivSales& operator=(const DivSales& other);

    double& operator[](int index);
    const double& operator[](int index) const;

    int getNumberOfPeriods() const;
    double getTotalSales() const;

    static void resetCorporateSales();
    static void addCorporateSales(double total);
    static double getCorporateSales();
};

#endif