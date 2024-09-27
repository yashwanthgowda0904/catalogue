#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

// Function to decode the value from the given base
long long decodeValue(const std::string &value, int base) {
    return strtoll(value.c_str(), nullptr, base);
}

// Function to perform Lagrange Interpolation
double lagrangeInterpolation(const std::vector<int>& x, const std::vector<long long>& y) {
    double result = 0;
    int n = x.size();

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - x[j]) / static_cast<double>(x[i] - x[j]);  // f(0) for constant term
            }
        }
        result += term;
    }

    return result;
}

int main() {
    std::ifstream inputFile("test_cases.json");
    json testCases;

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    inputFile >> testCases;
    inputFile.close();

    // Loop through each test case
    for (const auto& testCase : testCases) {
        int n = testCase["n"];
        int k = testCase["k"];
        std::vector<int> x = testCase["x"].get<std::vector<int>>();
        std::vector<long long> y;

        for (const auto& value : testCase["y"]) {
            y.push_back(decodeValue(value["value"], value["base"]));
        }

        // Finding the constant term (c) using Lagrange Interpolation
        double c = lagrangeInterpolation(x, y);

        // Output the result
        std::cout << "The constant term (c) for the test case is: " << c << std::endl;
    }

    return 0;
}
