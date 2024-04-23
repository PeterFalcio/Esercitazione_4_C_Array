#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Asset {
    double w;
    double r;
};

int main() {
    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    double S;
    int n;
    vector<Asset> assets;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        getline(ss, key, ';');

        if (key == "S") {
            ss >> S;
        } else if (key == "n") {
            ss >> n;
            assets.resize(n);
        } else if (key == "w") {
            for (int i = 0; i < n; ++i) {
                ss >> assets[i].w;
                ss.ignore(); // Ignore the delimiter
            }
        } else if (key == "r") {
            for (int i = 0; i < n; ++i) {
                ss >> assets[i].r;
                ss.ignore(); // Ignore the delimiter
            }
        }
    }

    file.close();

    // Calculating rate of return
    double rate_of_return = 0;
    for (const auto& asset : assets) {
        rate_of_return += asset.w * asset.r;
    }

    // Calculating final value of the portfolio
    double V = S * (1 + rate_of_return);

    // Writing results to file
    ofstream output("result.txt");
    if (!output.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    output << fixed << setprecision(2);
    output << "S = " << S << ", n = " << n << endl;
    output << "w = [ ";
    for (int i = 0; i < n; ++i) {
        output << assets[i].w << " ";
    }
    output << "]" << endl;
    output << "r = [ ";
    for (int i = 0; i < n; ++i) {
        output << assets[i].r << " ";
    }
    output << "]" << endl;
    output << "Rate of return of the portfolio: " << fixed << setprecision(4) << rate_of_return << endl;
    output << "V: " << V << endl;

    output.close();

    // Printing results to screen
    cout << "S = " << S << ", n = " << n << endl;
    cout << "w = [ ";
    for (int i = 0; i < n; ++i) {
        cout << assets[i].w << " ";
    }
    cout << "]" << endl;
    cout << "r = [ ";
    for (int i = 0; i < n; ++i) {
        cout << assets[i].r << " ";
    }
    cout << "]" << endl;
    cout << "Rate of return of the portfolio: " << fixed << setprecision(4) << rate_of_return << endl;
    cout << "V: " << V << endl;

    return 0;
}
