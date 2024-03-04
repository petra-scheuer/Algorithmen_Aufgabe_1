#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class DayPerformance {
public:
    int day;
    int month;
    int year;
    double open;
    double high;
    double low;
    double close;
    int volume;
    double adjClose;

    DayPerformance(int day, int month, int year, double open, double high, double low, double close, int volume, double adjClose)
            : day(day), month(month), year(year), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose) {}
};

class SingleStock {
public:
    std::string name;
    std::string wkn;
    std::string abbreviation;
    DayPerformance performance;
    int hasValue;

    SingleStock(std::string name, std::string wkn, std::string abbreviation, DayPerformance performance, int hasValue)
            : name(name), wkn(wkn), abbreviation(abbreviation), performance(performance), hasValue(hasValue) {}

    void printData() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "WKN: " << wkn << std::endl;
        std::cout << "Abbreviation: " << abbreviation << std::endl;
        std::cout << "Day Performance:" << std::endl;
        std::cout << "  Date: " << performance.day << "." << performance.month << "." << performance.year << std::endl;
        std::cout << "  Open: " << performance.open << std::endl;
        std::cout << "  High: " << performance.high << std::endl;
        std::cout << "  Low: " << performance.low << std::endl;
        std::cout << "  Close: " << performance.close << std::endl;
        std::cout << "  Adj Close: " << performance.adjClose << std::endl;
        std::cout << "  Volume: " << performance.volume << std::endl;
        std::cout << "Has Value: " << hasValue << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

int main() {
    std::ifstream file("ALGO.csv");
    if (!file.is_open()) {
        std::cerr << "Konnte die Datei nicht öffnen!" << std::endl;
        return 1;
    } else {
        std::cout << "Datei erfolgreich geöffnet!" << std::endl;
    }

    std::string line;
    std::getline(file, line);  // Ignoriere die erste Zeile (Überschrift)

    std::vector<SingleStock> stocks;

    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', '.');
        std::replace(line.begin(), line.end(), ';', ',');

        std::vector<std::string> tokens;
        std::istringstream tokenStream(line);
        std::string token;

        while (std::getline(tokenStream, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 8) {
            int day, month, year;
            sscanf(tokens[0].c_str(), "%d.%d.%d", &day, &month, &year);

            DayPerformance dayPerformance(day, month, year,
                                          std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]),
                                          std::stod(tokens[4]), std::stoi(tokens[6]), std::stod(tokens[5]));

            SingleStock stock(tokens[7], "", "", dayPerformance, 1);  // Dummy-Werte für WKN und Abkürzung, kann angepasst werden
            stocks.push_back(stock);
        }
    }

    file.close();

    for (const auto& stock : stocks) {
        stock.printData();
    }

    return 0;
}
