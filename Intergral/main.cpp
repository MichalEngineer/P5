#include <iostream>
#include <iomanip>
#include "integral.h"

int main() {
    long long intervals;
    int threads;

    std::cout << "Podaj liczbe podzialow przedzialu (np. 100000000): ";
    std::cin >> intervals;

    std::cout << "Podaj liczbe watkow (np. 4): ";
    std::cin >> threads;

    PiCalculator calculator(intervals, threads);
    double pi = calculator.calculate();
    double executionTime = calculator.getExecutionTime();

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Przyblizona wartosc liczby Pi: " << pi << "\n";
    std::cout << "Czas obliczen: " << executionTime << " sekund\n";

    return 0;
}
