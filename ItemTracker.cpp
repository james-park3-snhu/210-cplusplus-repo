/*
 *  CS210 PROJECT 3
 *  Student: James Park ID:2710902
 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

/*
 *  Item class to handle name, count, and printing
 */
class Item {  
public:
    void SetNameAndCount(string itemName, int itemCount) {
        name = itemName;
        count = itemCount;
    }
    string GetName() { return name; }
    int GetCount() { return count; }
    void IncrementCount() { count += 1; }
    void PrintName() { cout << name; }
    void PrintCount() { cout << count; }
    // Generate histogram for item count
    void PrintHistogram() {  
        for (int i = 0; i < count; ++i) {
            cout << "*";
        }
    }
private:
    string name;
    int count;
};


/*
 *  Main function to handle file I/O, itemList vector, and menu options
 */
int main() {

    // Variables for input file processing
    ifstream inFS;
    
    // Variables for storing item list
    vector<Item> itemList;
    Item currItem;
    string itemName;
    int i;
    bool matchedItem = false;

    // Variables for output file processing
    ofstream outFS;

    // Variables for menu option processing
    int menuChoice;
    string itemSearchTerm;

    /*
     *  Begin file I/O processing
     */
    // Open the INPUT file
    inFS.open("CS210_Project_Three_Input_File.txt");

    // Check if input file can be opened
    if (!inFS.is_open()) {
        cout << "Could not open the input file." << endl;
        return 1;
    }

    // Read first item name
    getline(inFS, itemName);

    // Read until end-of-file, set item info and add to itemList 
    while (!inFS.fail()) {

        // Set match boolean false before searching through item list
        matchedItem = false;

        // Iterate through itemList vector
        for (i = 0; i < itemList.size(); ++i) {

            // If name found in list, increment count
            if (itemList.at(i).GetName() == itemName) {
                itemList.at(i).IncrementCount();
                // set boolean found true
                matchedItem = true;
            }

        } // End itemList vector parsing
        
        // If item not found in list then create item and add to item list
        if (!matchedItem) {
            currItem.SetNameAndCount(itemName, 1);
            itemList.push_back(currItem);

        }
        
        // Clear the error state
        inFS.clear();
        
        // Reset match boolean for next loop
        matchedItem = false;

        // Read next item name
        getline(inFS, itemName);

    } // End of input file processing

    // Open the OUTPUT file
    outFS.open("frequency.dat");

    // Check if output file can be opened
    if (!outFS.is_open()) {
        cout << "Could not open the output file frequency.dat." << endl;
        return 1;
    }

    // Write to file
    for (i = 0; i < itemList.size(); ++i) {
        outFS << itemList.at(i).GetName() << " ";
        outFS << itemList.at(i).GetCount() << endl;
    }

    // Done with files, so close
    outFS.close();
    inFS.close();

    /*
     *  Begin menu functionality
     */
    menuChoice = 0;
    while (menuChoice != 4) {
        // Display menu options
        cout << "Corner Grocer Item Tracker" << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter Menu Option:" << endl;
        cout << "1 - Search Item Frequency" << endl;
        cout << "2 - Display Item Frequency Count" << endl;
        cout << "3 - Display Item Frequency Histogram" << endl;
        cout << "4 - Exit Program" << endl;
        cout << "------------------------------------" << endl;
        
        // Get user input
        cin >> menuChoice;

        // Decision logic for menu choice
        if (menuChoice == 1) {
            cout << "Enter item name:" << endl;
            cin >> itemSearchTerm;

            // Set boolean for item match
            matchedItem = false;

            // Iterate through itemList vector
            for (i = 0; i < itemList.size(); ++i) {
                
                // Display item and count for found item
                if ( itemList.at(i).GetName() == itemSearchTerm) {
                    cout << endl;
                    cout << "Item: ";
                    itemList.at(i).PrintName();
                    cout << ", Count: ";
                    itemList.at(i).PrintCount();
                    cout << endl;
                    cout << endl;
                    matchedItem = true;
                }

            } // End itemList vector parsing

            // Display message if item not matched
            if (!matchedItem) {
                cout << "Item not found." << endl;
                cout << endl;
                }
        }
        if (menuChoice == 2) {
            cout << endl;

            // Output summary item list with count
            for (i = 0; i < itemList.size(); ++i) {
                itemList.at(i).PrintName();
                cout << " ";
                itemList.at(i).PrintCount();
                cout << endl;
            }
            cout << endl;

        }
        if (menuChoice == 3) {
            cout << endl;

            // Output summary item list with count
            for (i = 0; i < itemList.size(); ++i) {
                itemList.at(i).PrintName();
                cout << " ";
                itemList.at(i).PrintHistogram();
                cout << endl;
            }
            cout << endl;

        }
        if (menuChoice == 4) {
            cout << "Goodbye" << endl;
            break;
        }
    }
    return 0;
}
