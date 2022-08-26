/* Author: Zachary Loschinskey
 * Date: 26 AUG 2022
 * Description: Create a hashmap to store phone numbers given a person name.
 *              Uses chaining to avoid collisions.
 */

#include <iostream>
#include <cstring>
#include <list>
using namespace std;

// Hashtable to implement ie. 901, Zach

class HashTable{
    private:
        static const int hashGroups = 10; // Number of unique hash groups
        list<pair<int, string>> table[hashGroups]; // List 1 at Index 0, List 2 at Index 1...
    
    public:
        bool isEmpty() const;
        int hashFunction(int key);
        void insertItem(int key, string value);
        void removeItem(int key);
        string searchTable(int key);
        void printTable();
};

bool HashTable::isEmpty() const {
    int sum = 0;

    for(int i=0; i<hashGroups; i++)
        sum += table[i].size();

    if(!sum)
        return true;
    return false;
}

int HashTable::hashFunction(int key){
    return key % hashGroups;

}

void HashTable::insertItem(int key, string value){
    // Find which cell to insert to
    int hashValue = hashFunction(key);

    // Check if value exists in cell already
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool exists = false;

    // Check if the key already exists in the list
    for(; bItr != end(cell); bItr++){
        if(bItr->first == key){
            exists = true;
            bItr->second = value;
            cout<<"[Warning] Key already in list. Value updated."<<endl;
            break;
        }
    }

    if(!exists){
        cell.emplace_back(key, value);
    }

    return;

}

void HashTable::removeItem(int key){
    // Find which cell to insert to
    int hashValue = hashFunction(key);

    // Check if value exists in cell already
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool exists = false;

    // Check if the key already exists in the list
    for(; bItr != end(cell); bItr++){
        if(bItr->first == key){
            exists = true;
            bItr = cell.erase(bItr);
            cout<<"[Info] Key found. Pair removed from table."<<endl;
            break;
        }
    }

    if(!exists){
        cout<<"[Warning] Key does not exist in table."<<endl;
    }

    return;

}

void HashTable::printTable(){
    for(int i = 0; i<hashGroups; i++){
        auto& cell = table[i];
        auto bItr = begin(cell);
        
        // Check if list is empty and skip it if so!
        if(cell.size() == 0)
            continue;

        for(; bItr != end(cell); bItr++){
            cout << "Key: " << bItr->first << " " << "Value: " << bItr->second << endl;
        }
    }

    return;

}


string HashTable::searchTable(int key){
    // Get hashvalue for the desired key
    int hashValue = hashFunction(key);

    // Find which list to look in
    auto& cell = table[hashValue];
    
    // Loop through the list to find the key
    auto bItr = begin(cell);

    bool found = false;

    for(; bItr != end(cell); bItr++){
        if(bItr->first == key){
            return bItr->second;
        }
    }

    return "[Warning] Key " + to_string(key) + " not found!";
}


int main(){

    HashTable Phonebook;

    Phonebook.insertItem(901, "Zachary");
    Phonebook.insertItem(314, "Isabel");
    Phonebook.insertItem(962, "Hubert Pelligrini");

    string searchVal = Phonebook.searchTable(314);
    cout<<searchVal<<endl;

    string searchVal2 = Phonebook.searchTable(111);
    cout<<searchVal2<<endl;

    return(0);
}