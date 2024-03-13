#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class DayPerformance {
private:
    int day;
    int month;
    int year;
    double open;
    double high;
    double low;
    double close;
    int volume;
    double adjClose;

public:
    DayPerformance(int day, int month, int year, double open, double high, double low, double close, int volume, double adjClose)
            : day(day), month(month), year(year), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose) {}

    // Public member functions to access private attributes
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    int getVolume() const { return volume; }
    double getAdjClose() const { return adjClose; }
};

class SingleStock {
private:
    std::string name;
    std::string wkn;
    std::string abbreviation;
    DayPerformance performance;
    int hasValue;

public:
    SingleStock(std::string name, std::string wkn, std::string abbreviation, const DayPerformance& performance, int hasValue)
            : name(name), wkn(wkn), abbreviation(abbreviation), performance(performance), hasValue(hasValue) {}

    // Public member functions to access private attributes
    std::string getName() const { return name; }
    std::string getWkn() const { return wkn; }
    std::string getAbbreviation() const { return abbreviation; }
    const DayPerformance& getPerformance() const { return performance; }
    int getHasValue() const { return hasValue; }

    void printData() const {
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "WKN: " << getWkn() << std::endl;
        std::cout << "Abbreviation: " << getAbbreviation() << std::endl;
        std::cout << "Day Performance:" << std::endl;
        std::cout << "  Date: " << getPerformance().getDay() << "." << getPerformance().getMonth() << "." << getPerformance().getYear() << std::endl;
        std::cout << "  Open: " << getPerformance().getOpen() << std::endl;
        std::cout << "  High: " << getPerformance().getHigh() << std::endl;
        std::cout << "  Low: " << getPerformance().getLow() << std::endl;
        std::cout << "  Close: " << getPerformance().getClose() << std::endl;
        std::cout << "  Adj Close: " << getPerformance().getAdjClose() << std::endl;
        std::cout << "  Volume: " << getPerformance().getVolume() << std::endl;
        std::cout << "Has Value: " << getHasValue() << std::endl;
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
    int lineNumber = 0;  // Startet mit 0, da die erste Datenzeile als Zeile 1 zählt

    while (std::getline(file, line)) {
        lineNumber++;  // Aktualisiere die Zeilennummer für jede gelesene Zeile

        // Zeilennummer-basierte Abkürzungs(Zeichencode)-Zuweisung
        std::string abbreviation;
        std::string name;

        if (lineNumber >= 1 && lineNumber <= 250) {
            abbreviation = "MSFT";
            name = "Microsoft Corporation";

        } else if (lineNumber >= 251 && lineNumber <= 504) {
            abbreviation = "RY4C";
            name = "Ryanair Holding";
        } else if (lineNumber >= 505 && lineNumber <= 755) {
            abbreviation = "TSLA";
            name = "Tesla, Inc.";
        } else if (lineNumber >= 756 && lineNumber <= 1008) {
            abbreviation = "PKTM";
            name = "PIERER Mobility AG";
        }

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

            SingleStock stock(name, "", abbreviation, dayPerformance, 1);  // Verwende `abbreviation` für die Abkürzung
            stocks.push_back(stock);
        }
    }

    file.close();

    for (const auto& stock : stocks) {
        stock.printData();
    }

    return 0;
}
