/*
Tristen Bradney
CS300
April 15, 2024
*/

// Include standard libraries.
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>



// Hash Table class template.
template<typename Key, typename Value>
class HashTable {
private:

    // Vector of key-value pairs.
    std::vector<std::pair<Key, Value>> table;

    // Capacity of the hash table.
    int capacity;

    // Hash function.
    int hash(Key key, int arraySize) {
        try {
            int hash = 0;

            // Iterate over each character in the key.
            for (char c : key) {

                // Apply hash function.
                hash = (hash * 31 + c) % arraySize;
            }
            return hash;
        }

        // Catch known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: hash." << std::endl;
        }

        // Catch unknown exception.
        catch (...) {
            std::cout << "Unknown exception occurred in function: hash." << std::endl;
        }
    }

    // Collision handling.
    void handleCollision(Key key, Value value, int arraySize) {
        try {

            // Calculate initial index.
            int index = hash(key, arraySize);

            // Linear probing for an empty slot.
            while (table[index].first != "") {

                // Move to the next slot.
                index = (index + 1) % arraySize;
            }

            // Insert key-value pair.
            table[index] = std::make_pair(key, value);
        }

        // Catch known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: handleCollision." << std::endl;
        }

        // Catch unknown exceptions.
        catch (...) {
            std::cout << "Unknown exception occurred in function: handleCollision." << std::endl;
        }
    }

public:

    // Constructor.
    HashTable(int initialCapacity) : capacity(initialCapacity) {

        // Resize the table.
        table.resize(capacity);
    }

    // Insert method
    void insert(Key key, Value value) {
        try {

            // Calculate hash.
            int index = hash(key, table.size());

            // Check if slot is empty.
            if (table[index].first == "") {

                // Insert key-value pair.
                table[index] = std::make_pair(key, value);
            }
            else {

                // Handle collision.
                handleCollision(key, value, table.size());
            }
        }

        // Handle known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: insert." << std::endl;
        }

        // Handle unknown exceptions.
        catch (...) {
            std::cout << "Unknown exception occurred in function: insert." << std::endl;
        }
    }

    // Get method.
    Value get(Key key) {
        try {

            // Calculate hash.
            int index = hash(key, table.size());

            // Search for the index.
            while (table[index].first != key && table[index].first != "") {

                // Move to the next slot.
                index = (index + 1) % table.size();
            }

            // If key found.
            if (table[index].first == key) {

                // Return corresponding value.
                return table[index].second;
            }

            // Key not found.
            throw std::out_of_range("Key not found");
        }

        // Handle known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: get." << std::endl;
            return Value();
        }

        // Handle unknown exceptions.
        catch (...) {
            std::cout << "Unknown exception occurred in function: get." << std::endl;
            return Value();
        }
    }

    bool find(Key key) {
        try {

            // Calculate hash.
            int index = hash(key, table.size());

            // Search for the index.
            while (table[index].first != key && table[index].first != "") {

                // Move to the next slot.
                index = (index + 1) % table.size();
            }

            // If key found, return true.
            if (table[index].first == key) {

                // Return corresponding value.
                return true;
            }

            // Key not found.
            return false;
        }

        // Handle known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: find." << std::endl;
            return false;
        }

        // Handle unknown exceptions.
        catch (...) {
            std::cout << "Unknown exception occurred in function: find." << std::endl;
            return false;
        }
    }

    // Method to iterate over elements.
    std::vector<std::pair<Key, Value>> getAllElements() const {
        try {

            // Return all elements in the table.
            return table;
        }

        // Handle known exceptions.
        catch (const std::exception& e) {
            std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: getAllElements." << std::endl;
        }

        // Handle unknown exceptions.
        catch (...) {
            std::cout << "Unknown exception occurred in function: getAllElements." << std::endl;
        }
    }
};

// Define Courses class.
class Courses {
private:

    // Data structure to hold course information.
    struct Course {

        // Course number.
        std::string courseNumber;

        // Course title.
        std::string title;

        // Course prerequisites.
        std::vector<std::string> prerequisites;
    };

    // Flag to track if data is loaded.
    bool dataLoaded = false;

    // Hash table to store courses.
    HashTable<std::string, Course> table;

    // Print alphanumerically sorted list of courses.
    void printCourseList();

    // Print course details.
    void printCourse(const std::string& courseNumber);


public:

    // Constructor.
    // Set capacity to 10. Capacity should be increased for larger input files. Consider rehashing and dynamic hash table creation.
    Courses() : table(10) {};

    // Load data from file into the data structure.
    void loadDataStructure(const std::string& filename);

    // Executes program loop.
    int runProgram();
};

// Load data from file into the data structure.
void Courses::loadDataStructure(const std::string& filename) {
    try {
        dataLoaded = false;

        std::cout << "Loading data from file: " << filename << std::endl;

        // Open file stream.
        std::ifstream file(filename);

        // Check if file is opened successfully.
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file." << std::endl;
            return;
        }

        // Check for BOM and skip if present.
        if (file.peek() == 0xEF) {
            char dummy[3];
            file.read(dummy, 3);
        }

        std::vector<std::string> courseNumbers;
        std::vector<Course> parsedCourses;
        std::string line = "";

        // Parse lines in input file and fill courseNumbers and parsedCourses.
        while (std::getline(file, line)) {

            // Read file line by line.
            std::stringstream ss(line);
            Course course;
            std::string prerequisites;

            // Read comma-separated values from the line.
            std::getline(ss, course.courseNumber, ',');
            std::getline(ss, course.title, ',');
            
            // If there are prerequisites, read them.
            if (std::getline(ss, prerequisites)) {

                // Split the prerequisites into a vector.
                std::stringstream prerequisitesStream(prerequisites);

                std::string prerequisite;
                while (std::getline(prerequisitesStream, prerequisite, ',')) {

                    // Trim whitespace.
                    prerequisite.erase(0, prerequisite.find_first_not_of(" \t"));
                    prerequisite.erase(prerequisite.find_last_not_of(" \t") + 1);
                    course.prerequisites.push_back(prerequisite);
                }
            }
            courseNumbers.push_back(course.courseNumber);
            parsedCourses.push_back(course);
        }

        // Validate and insert valid courses into hash table.
        for (int i = 0; i <= parsedCourses.size() - 1; i++) {
            if (parsedCourses[i].prerequisites.size() == 0) {
                table.insert(parsedCourses[i].courseNumber, parsedCourses[i]);
                continue;
            }

            bool isValid = true;

            for (int j = 0; j <= parsedCourses[i].prerequisites.size() - 1; j++) {
                std::vector<std::string>::iterator it; 
                it = find(courseNumbers.begin(), courseNumbers.end(), parsedCourses[i].prerequisites[j]);
                if (it == courseNumbers.end()) {
                    std::cout << "Failed to find prerequisite " << parsedCourses[i].courseNumber << " for " << parsedCourses[i].prerequisites[j] << std::endl;
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                table.insert(parsedCourses[i].courseNumber, parsedCourses[i]);
            }
        }

        std::cout << "Data loading complete." << std::endl;

        // Close file stream.
        file.close();

        // Set data loaded flag to true.
        dataLoaded = true;
    }

    // Handle known exceptions.
    catch (const std::exception& e) {
        std::cerr << "Known exception occurred: " << e.what() << std::endl << "in function: loadDataStructure." << std::endl;
    }

    // Handle unknown exceptions.
    catch (...) {
        std::cout << "Unknown exception occurred in function: loadDataStructure." << std::endl;
    }
}

// Print alphanumerically sorted list of courses.
void Courses::printCourseList() {
    try {
        
        // Check if data is loaded.
        if (!dataLoaded) {
            std::cout << "Course list is empty." << std::endl;
            std::cout << "Please load data structure first." << std::endl;
            return;
        }

        std::vector<std::string> courseNumbers;

        // Get all elements from the hash table.
        auto elements = table.getAllElements();
        for (const auto& entry : elements) {

            // Push course numbers into vector if not empty.
            if (!entry.first.empty()) {
                courseNumbers.push_back(entry.first);
            }
        }

        // Set course numbers.
        std::sort(courseNumbers.begin(), courseNumbers.end());

        std::cout << "Alphanumeric list of courses: " << std::endl;
        for (const auto& courseNumber : courseNumbers) {

            // Print course number and title.
            std::cout << courseNumber << ", " << table.get(courseNumber).title << std::endl;
        }
    }

    // Handle known exceptions.
    catch (const std::exception& e) {
        std::cout << "Known exception occurred: " << e.what() << std::endl << "in function: printCourseList." << std::endl;
    }

    // Handle unknown exceptions.
    catch (...) {
        std::cout << "Unknown exception occurred in function: printCourseList." << std::endl;
    }
}

// Print course details.
void Courses::printCourse(const std::string& courseNumber) {
    try {

        if (table.find(courseNumber) == false) {
            throw std::out_of_range("Course not found");
        }

        // Search for the course by its number (case-sensitive).
        Course course = table.get(courseNumber);

        // Print course details.
        std::cout << course.courseNumber << ", " << course.title << std::endl;
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites:" << std::endl;
            for (const auto& prerequisite : course.prerequisites) {
                std::cout << "   " << prerequisite << std::endl;
            }
        }

        // Print if no prerequisites.
        else {
            std::cout << "No prerequisites." << std::endl;
        }
    }

    // Handle known exceptions.
    catch (const std::out_of_range& e) {
        std::cout << "Course not found." << std::endl;
    }

    // Handle unknown excpeptions.
    catch (const std::exception& e) {
        std::cout << "Exception occurred: " << e.what() << std::endl;
    }
}

// Executes program loop.
int Courses::runProgram() {
    try {
        std::string filename, courseNumber;
        std::string input;
        int choice;

        std::cout << "Welcome to the course planner." << std::endl;

        do {
            std::cout << "1. Load Data Structure." << std::endl;
            std::cout << "2. Print Course List." << std::endl;
            std::cout << "3. Print Course." << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "What would you like to do? ";
            std::getline(std::cin, input);

            std::stringstream ss(input);
            ss >> choice;

            switch (choice) {
            case 1:
                try {

                    std::cout << "Please enter input file name." << std::endl;
                    std::getline(std::cin, filename);

                    loadDataStructure(filename);

                    if (dataLoaded) {
                        std::cout << "Data loaded successfully." << std::endl;
                    }
                    else {
                        std::cout << "Failed to load data." << std::endl;
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                if (!dataLoaded) {
                    std::cout << "Course list is empty." << std::endl;
                    std::cout << "Please load data structure first." << std::endl;
                    break;
                }
                std::cout << "Enter the course number: ";
                std::cin >> courseNumber;

                // Clear the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                printCourse(courseNumber);
                break;
            case 4:
                std::cout << "Thank you for using the course planner!" << std::endl;
                break;
            default:
                std::cout << input << " is not a valid option." << std::endl;
            }
        } while (choice != 4);
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Known exception occurred: " << e.what() << std::endl << "in function: runProgram." << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception occurred in function: runProgram." << std::endl;
    }
}

// Program entry.
int main() {

    // Instantiate Courses class and run program.
    Courses courses;
    courses.runProgram();

    // Program successfully executed.
    return 0;
}
