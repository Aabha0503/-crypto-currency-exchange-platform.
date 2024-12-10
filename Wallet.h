#pragma once
#include <iostream>
#include <string>
#include <map>
#include "CSVReader.h"
#include"OrderBook.h"
#include "OrderBookEntry.h"
using namespace std;
class Wallet {
public:
    Wallet(); // Constructor

    // Method to insert currency into the wallet
    void insertCurrency(std::string type, double amount);

    // Method to check if the wallet contains the specified amount of a currency
    bool containsCurrency(std::string type, double amount);

    // Method to return a string representation of the wallet
    std::string toString(); // Corrected from String to std::string

    bool removeCurrency(std::string type, double amount);

    bool canFulfillOrder(OrderBookEntry order);

    void processSale(OrderBookEntry & sale);

private:
    std::map<std::string, double> currencies; // Map to store currency and its amount
};
