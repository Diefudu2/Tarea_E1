#include <iostream>
#include "IS.cpp"
using namespace std;

int main() {
    int arr[] = { 12, 11, 13, 5, 6 };
	int N = sizeof(arr) / sizeof(arr[0]);

	insertionSort(arr, N);
    printArray(arr, N);
    return 0;
}
