// Include local header file.
#include "GroceryTracker.h"

// Constructor for the GroceryTracker class.
GroceryTracker::GroceryTracker() {
    try {

        // Attempt to read data from input file.
        readDataFromFile();
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: GroceryTracker." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: GroceryTracker." << std::endl;
    }
}

// Function to read data from a file and update the m_itemFrequency map.
void GroceryTracker::readDataFromFile() {
    try {

        // Open the input file.
        std::ifstream inputFile("CS210_Project_Three_Input_File.txt");

        // Check if the input file is open.
        if (inputFile.is_open()) {

            // Variable to store the item name read from the file.
            std::string itemName;

            // Read items from the file and update their frequency in the m_itemFrequency map. 
            while (inputFile >> itemName) {
                if (m_itemFrequency.count(itemName)) {

                    // Increment the frequency if the item already exists in the map. 
                    m_itemFrequency[itemName] += 1;
                }
                else {

                    // Add a new entry with a frequency of 1 if the item is encountered for the first time.
                    m_itemFrequency[itemName] = 1;
                }
            }

            // Close the file after reading.
            inputFile.close();
        }
        else {

            // Display an error message if unable to open the input file.
            std::cerr << "Unable to open input file." << std::endl;
        }
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: readDataFromFile." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: readDataFromFile." << std::endl;
    }
}

// Function to display the menu options.
void GroceryTracker::displayMenu() {
    try {

        // Display a menu with numberd options to the user. 
        std::cout << "===============  Menu  =================" << std::endl;
        std::cout << "1. Search for an item" << std::endl;
        std::cout << "2. Display frequency of all items" << std::endl;
        std::cout << "3. Display histogram of item frequencies" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "========================================" << std::endl;
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions, if any. 
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: displayMenu." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: displayMenu." << std::endl;
    }
}

// Function to search for the frequency of a specific item in the m_itemFrequency map.
void GroceryTracker::searchItem() {
    try {

        // Declare a variable to store the item that the user wishes to search for.
        std::string searchItem;

        // Prompt the user to enter the item they wish to search for. 
        std::cout << "Enter the item you wish to search for: " << std::endl;
        std::cin >> searchItem;

        for (auto& x : searchItem) {
            x = tolower(x);
        }
        
        // Capitalize the first letter of the item.
        searchItem[0] = std::toupper(searchItem[0]);

        // Attempt to find the entered item in the m_itemFrequency map.
        auto it = m_itemFrequency.find(searchItem);

        // Check if the item was found.
        if (it != m_itemFrequency.end()) {

            // If found, display the frequency of the item.
            std::cout << "Frequency of " << searchItem << ": " << it->second << std::endl;
        }
        else {

            // If not found, inform the user.
            std::cout << searchItem << " not found in records.\n";
        }
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: searchItem." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: searchItem." << std::endl;
    }
}

// Function to display the frequency of all items in the m_itemFrequency map.
void GroceryTracker::displayAllItems() {
    try {

        // Iterate through each item-frequency pair in the m_itemFrequency map.
        for (const auto& pair : m_itemFrequency) {

            // Display the item name and its corresponding frequency. 
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: displayAllItems." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: displayAllItems." << std::endl;
    }
}

// Function to display a histogram representing the frequency of items in the m_itemFrequency map.
void GroceryTracker::displayHistogram() {
    try {

        // Iterate through each item-frequency pair in the m_itemFrequency map.
        for (const auto& pair : m_itemFrequency) {

            // Display the item name.
            std::cout << pair.first << " ";

            // Display '*' for each occurance of the item, creating a histogram.
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }

            // Move to the next line after displaying the histogram for the current item.
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: displayHistogram." << std::endl;
    }
    catch (...) {

        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: displayHistogram." << std::endl;
    }
}

// Function to save the item frequency data to a backup file named "frequency.dat".
void GroceryTracker::saveDataToBackup() {
    try {

        // Open the backup file for writing.
        std::ofstream backupFile("frequency.dat");

        // Check if the file is open.
        if (backupFile.is_open()) {

            // Iterate through each item-frequency pair in the m_itemFrequency map.
            for (const auto& pair : m_itemFrequency) {

                // Write the item name and its corresponding frequency to the backup file.
                backupFile << pair.first << " " << pair.second << std::endl;
            }

            // Close the backup file after writing.
            backupFile.close();
        }
        else {

            // Display an error message if unable to open the backup file for writing.
            std::cerr << "Unable to open backup file for writing." << std::endl;
        }
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: saveDataToBackup." << std::endl;
    }
    catch (...) {
        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: saveDataToBackup." << std::endl;
    }
}

// Executes grocery tracker program loop.
void GroceryTracker::runProgram() {
    try {

        // Declare empty variable named choice to store user input.
        int choice;

        // Execute the following block of code at least once, and repeat as long as choice is not equal to 4.
        do {

            // Display options menu to user.
            displayMenu();

            // Prompt user for input.
            std::cout << "Enter your choice: " << std::endl;

            // Check if the input is the expected type (integer).
            while (!(std::cin >> choice)) {

                // Clear the error flag for cin.
                std::cin.clear();

                // Discard the invalid input.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Prompt the user again.
                std::cout << "Invalid input. Please enter an integer." << std::endl;

                // Display options menu to user. 
                displayMenu();
            }

            // Discard the invalid input.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Check the user's choice to determine the action to perform.
            if (choice == 1) {

                // If choice is 1, call the searchItem() method of the groceryTracker object.
                searchItem();
            }

            else if (choice == 2) {

                // If choice is 2, call the displayAllItems() method of the groceryTracker object.
                displayAllItems();
            }

            else if (choice == 3) {

                // If choice is 3, call the displayHistogram() method of the groceryTracker object.
                displayHistogram();
            }

            else if (choice == 4) {

                // If choice is 4, call saveDataToBackup() method of the groceryTracker object.
                saveDataToBackup();

                // Display a message indicating that the backup has been saved.
                std::cout << "Exiting program. Backup saved to frequency.dat." << std::endl;
            }

            else {

                // If none of the above conditions match, display an error message.
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 4);
    }
    catch (const std::exception& e) {

        // Catch and handle known exceptions.
        std::cout << "Known exception occured: " << e.what() << std::endl << "in function: runProgram." << std::endl;
    }
    catch (...) {
        // Catch and handle unknown exceptions.
        std::cout << "Unknown exception occured in function: runProgram." << std::endl;
    }
}
