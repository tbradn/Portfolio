#pragma once
#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

// Include standard libraries.
#include <iostream>
#include <fstream>
#include <map>
#include <string>

// Define GroceryTracker class.
class GroceryTracker {

// Internally available methods and variables.
private:

    // A map for associating individual items with their corresponding frequency counts.
    std::map<std::string, int> m_itemFrequency;

    // Read data from local .txt file for item information.
    void readDataFromFile();

    // Display options menu to user.
    void displayMenu();

    // Display frequency of specified item from the .txt file.
    void searchItem();

    // Display frequency of all items from the .txt file.
    void displayAllItems();

    // Display historgram representing the frequency of all items from the .txt file.
    void displayHistogram();

    // Save frequency data to .dat file.
    void saveDataToBackup();

// Externally available methods.
public:

    // Constructor.
    GroceryTracker();

    // Destructor.
    ~GroceryTracker() {};

    // Executes grocery tracker program loop.
    void runProgram();
};

#endif // GROCERY_TRACKER_H
