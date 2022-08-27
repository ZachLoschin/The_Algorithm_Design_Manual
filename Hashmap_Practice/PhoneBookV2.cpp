/* Author: Zachary Loschinskey
 * Date: 27 AUG 2022
 * Description: Create a hashmap to store phone numbers given a person name.
 *              Uses chaining to avoid collisions.
 * 
 *              This phonebook will allow you to search by name in the book and get returned a their full phone number.
 *              I would also like to play around with saving and loading the hashmap for long term storage.
 */

#include <iostream>
#include <list>
#include <cstring>
using namespace std;

// Create the HashTable class: key is name of person value is their phone number

class HashTable{
    private:
        static const int hashGroups = 50; // Create 50 hashGroups
        list<pair<string, int>> table[hashGroups]; // Initialize lists of pairs in each element of our table


    public:
        bool isEmpty();
        void insertElement(string, int);
        void deleteElement(string);
        int convertToASCII(string);
        int hashFunction(string);
        void displayTable();
        int searchTable(string);

};

bool HashTable::isEmpty(){
    // Check if the sum of the lists in the table is zero
    int sum = 0;

    // Go through each list of table and add its size to our sum var
    for(int i=0; i < hashGroups; i++)
        sum += table[i].size();

    // If the sum is zero, the table is empty
    if(!sum)
        return true;
    return false;
}

int HashTable::convertToASCII(string key){
    // Convert string to the sum of its ASCII character values
    
    int sumASCII = 0;
    
    for(int i=0; i<key.length(); i++){
        sumASCII += (int)key[i]; // Casting to int converts char -> ASCII int
    }

    return sumASCII;
}

int HashTable::hashFunction(string key){

    return convertToASCII(key) % hashGroups; // Return sum of ASCII values scaled to our number of groups
}

void HashTable::insertElement(string key, int value){
    // Insert an int value into table using string key

    // Find which list to insert to
    int hashValue = hashFunction(key);

    // Get the address of that list
    auto& cell = table[hashValue];

    // Check to see if this key already exists in the list
    bool exists = false;

    auto itr = begin(cell);
    for(; itr != end(cell); itr++){
        if(itr->first == key){
            exists = true;
            itr->second = value;
            cout << "[Warning] Key already " + key + " exists in table. Value updated." << endl;
        }
    }

    if(!exists){
        cell.emplace_back(key, value);
        cout << "[Note] Key " + key + " added to table." << endl;
    }

    return;
}

void HashTable::deleteElement(string key){
    // Remove an element from the table and alert user if this key/value pair doesn't exist

    // Find which list to search in for key
    int hashValue = hashFunction(key);

    // Get the address of that list
    auto& cell = table[hashValue];

    // Check to see if this key already exists in the list
    bool exists = false;

    auto itr = begin(cell);
    for(; itr != end(cell); itr++){
        if(itr->first == key){
            exists = true;
            itr = cell.erase(itr); // Remove the key value pair
            cout << "[Info] Key " + key + " removed from the table." << endl;
        }
    }

    // Alert user if they try to remove a key that isn't in the table
    if(!exists){
        cout << "[Warning] Key " + key + " doesn't exist in table." << endl;
    }

    return;
}

void HashTable::displayTable(){
    // Display the contents of the table to user

    // Loop through the hashGroups
    for(int i=0; i<hashGroups; i++){
        // Check if list is empty. If not display contents
        auto& cell = table[i];

        if(cell.size() == 0)
            continue;

        auto itr = begin(cell);

        for(; itr != end(cell); itr++)
            cout << "Key: " << itr->first << " Value: " << itr->second << endl;

    }

    return;
}

int HashTable::searchTable(string key){
    // Get hashvalue for the desired key
    int hashValue = hashFunction(key);

    // Find which list to look in
    auto& cell = table[hashValue];
    
    // Loop through the list to find the key
    auto bItr = begin(cell);

    bool found = false;

    for(; bItr != end(cell); bItr++){
        if(bItr->first == key){
            found = true;
            return bItr->second;
        }
    }

    if(!found){
        cout << "[Warning] Key: " << key << " not found in table";
    }
    
    return -1;
}


int main(){

    // Create a phone book
    HashTable Phonebook;

    // Add a few people (fake numbers)

    Phonebook.insertElement("Zachary Loschinskey", 1231);
    Phonebook.insertElement("Isabel Banks", 3140);
    Phonebook.insertElement("Arsene Lupin", 5550);

    // Display the phone book
    Phonebook.displayTable();

    // Remove someone from the phone book
    Phonebook.deleteElement("Zachary Loschinskey");

    // Display the table once more
    Phonebook.displayTable();

    // Try to remove someone who doesn't exist in the table
    Phonebook.deleteElement("Bad Bunny");

    // Search for someones number
    Phonebook.searchTable("Arsene Lupin");

    return(0);
}