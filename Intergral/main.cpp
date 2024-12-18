#include <iostream>
#include <iomanip>
#include <fstream>
#include "integral.h"

void runTests() {
    // Lista liczby podzia³ów i w¹tków
    const std::vector<long long> intervalsList = { 100000000, 1000000000, 3000000000 };
    const int maxThreads = 50;

    // Plik wynikowy
    std::ofstream resultsFile("results.csv");
    resultsFile << "Intervals,Threads,Time (s),Pi Approximation\n";

    for (auto intervals : intervalsList) {
        for (int threads = 1; threads <= maxThreads; ++threads) {
            PiCalculator calculator(intervals, threads);
            double pi = calculator.calculate();
            double time = calculator.getExecutionTime();

            // Zapis wyników do pliku
            resultsFile << intervals << "," << threads << "," << time << "," << pi << "\n";
            std::cout << "Intervals: " << intervals
                << ", Threads: " << threads
                << ", Time: " << time
                << " s, Pi: " << pi << "\n";
        }
    }

    resultsFile.close();
    std::cout << "Testy zakoñczone. Wyniki zapisano w pliku 'results.csv'.\n";
}

int main() {
    int option;
    std::cout << "Wybierz opcje:\n";
    std::cout << "1 - Uruchom testy automatyczne i zapisz wyniki\n";
    std::cout << "2 - Oblicz Pi dla podanej liczby podzia³ów i w¹tków\n";
    std::cin >> option;

    if (option == 1) {
        runTests();
    }
    else if (option == 2) {
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
    }
    else {
        std::cout << "Niepoprawna opcja. Koniec programu.\n";
    }

    return 0;
}
