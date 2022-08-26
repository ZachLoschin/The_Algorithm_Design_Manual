/* Author: Zachary Loschinskey
 * Date: 26 AUG 2022
 * Description: Simple implementation of selection sort
*/

#include <iostream>
#include <random>
using namespace std;

#define SIZE 10 // Size for the array

void print_array(int* inpArray, int size);
void rand_array(int* inpArray, int size);
void selection_sort(int* inpArray, int size);
void swap(int &a, int &b);
void selection_sort(int* inpArray, int size);

int main(){

    // Generate a random array and display it
    int a[SIZE];
    rand_array(a, SIZE);
    print_array(a, SIZE);

    // Sort the array
    selection_sort(a, SIZE);
    print_array(a, SIZE);

    return(0);
}

void print_array(int* inpArray, int size){
    int i; // iterator

    for(i=0; i<size; i++)
        cout << *(inpArray + i) << " ";
    
    cout << endl;
}

void rand_array(int* inpArray, int size){
    int i; // iterator

    for(i=0; i<size; i++)
        *(inpArray + i) = rand() % 100 + 1; // Random int from 1-100
}

void selection_sort(int* inpArray, int size){

    int i, j; // iterators

    for(i=0; i<size; i++){

        int minIndex = i;

        for(j=i+1; j<size; j++){

            if(inpArray[j] < inpArray[minIndex])
                minIndex = j;
        }

        swap(inpArray[minIndex], inpArray[i]);
    }
}

void swap(int &a, int &b){
    int temp; // to not lose data

    temp = a;
    a = b;
    b = temp;

}