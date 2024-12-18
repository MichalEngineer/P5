/**
 * @file main.cpp
 * @brief G��wny plik programu do obliczania liczby Pi za pomoc� numerycznej ca�ki.
 *
 * @details
 * Program oferuje dwa tryby dzia�ania:
 * - Uruchomienie test�w automatycznych dla r�nych liczby podzia��w i w�tk�w.
 * - R�czne obliczanie przybli�onej warto�ci liczby Pi dla podanej liczby podzia��w i w�tk�w.
 *
 * Wyniki test�w s� zapisywane w pliku CSV, a u�ytkownik mo�e �ledzi� czas oblicze� oraz przybli�on� warto�� liczby Pi.
 *
 * ## Wykorzystywane biblioteki:
 * - `<iostream>`: Standardowa biblioteka wej�cia/wyj�cia, u�ywana do komunikacji z u�ytkownikiem (wypisywanie wynik�w i pobieranie danych).
 * - `<iomanip>`: Biblioteka do manipulacji formatem wyj�cia, u�ywana w celu ustawienia precyzyjno�ci wy�wietlanej warto�ci liczby Pi.
 * - `<fstream>`: Biblioteka umo�liwiaj�ca zapis wynik�w do pliku CSV.
 * - `"integral.h"`: Nag��wek klasy `PiCalculator` zawieraj�cej metody obliczania liczby Pi.
 */

#include <iostream>   ///< Biblioteka do obs�ugi wej�cia/wyj�cia, w tym wypisywania na ekranie.
#include <iomanip>    ///< Biblioteka do manipulacji formatem wyj�cia (np. ustawianie precyzji liczby zmiennoprzecinkowej).
#include <fstream>    ///< Biblioteka do obs�ugi plik�w, w tym zapisywania wynik�w do pliku CSV.
#include "integral.h" ///< Nag��wek klasy PiCalculator, zawieraj�cy deklaracje metod obliczaj�cych liczb� Pi.

 /**
  * @brief Funkcja do uruchamiania test�w automatycznych oblicze� liczby Pi dla r�nych liczby podzia��w i w�tk�w.
  *
  * @details
  * Funkcja ta przeprowadza testy automatyczne, obliczaj�c warto�� liczby Pi dla r�nych liczby podzia��w
  * i w�tk�w. Wyniki s� zapisywane w pliku CSV oraz wypisywane na ekranie.
  */
void runTests() {
    // Lista liczby podzia��w (w r�nych skalach) u�ywanych w testach.
    const std::vector<long long> intervalsList = { 100000000, 1000000000, 3000000000 };

    // Maksymalna liczba w�tk�w, kt�re b�d� testowane w ramach test�w automatycznych.
    const int maxThreads = 50;

    // Otwarcie pliku wynikowego, do kt�rego b�d� zapisywane rezultaty test�w w formacie CSV.
    std::ofstream resultsFile("results.csv");

    // Zapisanie nag��wka do pliku CSV (nag��wki dla ka�dego typu danych, kt�ry b�dzie zapisywany).
    resultsFile << "Intervals,Threads,Time (s),Pi Approximation\n";

    // P�tla przechodz�ca przez ka�dy przypadek liczby podzia��w (z listy intervalsList).
    for (auto intervals : intervalsList) {
        // P�tla przechodz�ca przez liczb� w�tk�w, kt�re b�d� testowane.
        for (int threads = 1; threads <= maxThreads; ++threads) {
            // Tworzenie obiektu kalkulatora, kt�ry obliczy warto�� Pi dla aktualnej liczby podzia��w i w�tk�w.
            PiCalculator calculator(intervals, threads);

            // Obliczanie przybli�onej warto�ci liczby Pi oraz czasu potrzebnego na obliczenie.
            double pi = calculator.calculate();
            double time = calculator.getExecutionTime();

            // Zapisanie wynik�w oblicze� do pliku CSV (liczba podzia��w, liczba w�tk�w, czas wykonania, przybli�ona warto�� Pi).
            resultsFile << intervals << "," << threads << "," << time << "," << pi << "\n";

            // Wypisanie wynik�w na ekranie dla u�ytkownika.
            std::cout << "Intervals: " << intervals
                << ", Threads: " << threads
                << ", Time: " << time
                << " s, Pi: " << pi << "\n";
        }
    }

    // Zamkni�cie pliku po zako�czeniu zapisywania wynik�w.
    resultsFile.close();

    // Wypisanie komunikatu, �e testy zosta�y zako�czone, a wyniki zosta�y zapisane w pliku.
    std::cout << "Testy zako�czone. Wyniki zapisano w pliku 'results.csv'.\n";
}

/**
 * @brief Funkcja g��wna programu, kt�ra umo�liwia wyb�r trybu dzia�ania programu.
 *
 * @details
 * Program dzia�a w dw�ch trybach:
 * - Uruchomienie test�w automatycznych.
 * - R�czne obliczanie liczby Pi dla podanych przez u�ytkownika parametr�w.
 *
 * U�ytkownik wybiera tryb dzia�ania, a nast�pnie program realizuje odpowiedni� funkcjonalno��.
 * Wyniki oblicze� s� wy�wietlane na ekranie i zapisywane w pliku CSV w przypadku test�w automatycznych.
 *
 * @return 0 je�li program zako�czy� si� poprawnie.
 */
int main() {
    // Zmienna przechowuj�ca wyb�r u�ytkownika.
    int option;

    // Wy�wietlenie komunikatu z pro�b� o wyb�r jednej z dw�ch opcji.
    std::cout << "Wybierz opcje:\n";
    std::cout << "1 - Uruchom testy automatyczne i zapisz wyniki\n";
    std::cout << "2 - Oblicz Pi dla podanej liczby podzia��w i w�tk�w\n";

    // Wczytanie wyboru u�ytkownika.
    std::cin >> option;

    // Je�li u�ytkownik wybierze opcj� 1, uruchomimy testy automatyczne.
    if (option == 1) {
        runTests();  ///< Uruchomienie funkcji przeprowadzaj�cej testy automatyczne.
    }
    // Je�li u�ytkownik wybierze opcj� 2, zapytamy go o parametry i obliczymy liczb� Pi.
    else if (option == 2) {
        long long intervals;  ///< Zmienna do przechowywania liczby przedzia��w.
        int threads;          ///< Zmienna do przechowywania liczby w�tk�w.

        // Poproszenie u�ytkownika o podanie liczby przedzia��w do oblicze�.
        std::cout << "Podaj liczbe podzialow przedzialu (np. 100000000): ";
        std::cin >> intervals;

        // Poproszenie u�ytkownika o podanie liczby w�tk�w do oblicze�.
        std::cout << "Podaj liczbe watkow (np. 4): ";
        std::cin >> threads;

        // Utworzenie obiektu kalkulatora z odpowiednimi parametrami.
        PiCalculator calculator(intervals, threads);

        // Obliczenie liczby Pi i czasu oblicze�.
        double pi = calculator.calculate();
        double executionTime = calculator.getExecutionTime();

        // Wy�wietlenie wynik�w na ekranie z ustawion� precyzj� na 15 miejsc po przecinku.
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "Przyblizona wartosc liczby Pi: " << pi << "\n";
        std::cout << "Czas obliczen: " << executionTime << " sekund\n";
    }
    // Je�li u�ytkownik poda niepoprawn� opcj�, wy�wietlamy komunikat o b��dzie.
    else {
        std::cout << "Niepoprawna opcja. Koniec programu.\n";
    }

    // Zwr�cenie warto�ci 0, co oznacza zako�czenie programu bez b��d�w.
    return 0;
}
