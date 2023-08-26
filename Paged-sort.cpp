#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring> 
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <stdbool.h>
#include <stdio.h>
using namespace std;

const int PAGE_SIZE = 1024; // Tamaño de página en bytes
const int MAX_PAGES = 6;    // Número máximo de páginas

class Page {
public:
    std::vector<int> data;

    Page() {
        data.reserve(PAGE_SIZE / sizeof(int));
    }
};

class PagedArray {
public:
    void storeArray(const std::vector<int>& arr) {
        if (arr.size() * sizeof(int) > PAGE_SIZE) {
            std::cout << "El archivo es demasiado grande para una página. No se puede manejar." << std::endl;
            return;
        }

        if (pages.size() >= MAX_PAGES) {
            int pageToReplaceId = fifoQueue.front();
            fifoQueue.pop();

            std::cout << "Reemplazando página " << pageToReplaceId << " con nuevo archivo" << std::endl;

            pages[pageToReplaceId].data = arr;
            fifoQueue.push(pageToReplaceId);
        } else {
            Page newPage;
            newPage.data = arr;
            pages.push_back(newPage);
            fifoQueue.push(pages.size() - 1);
        }
    }

    std::vector<Page>& getPages() {
        return pages;
    }

private:
    std::vector<Page> pages;
    std::queue<int> fifoQueue;
};

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(Page& page, int n)
{
	std::vector<int>& arr = page.data;
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++) {
		swapped = false;
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}

		// If no two elements were swapped by inner loop,
		// then break
		if (swapped == false)
			break;
	}
}

// Function to sort an array using
// insertion sort
void insertionSort(Page& page, int n)
{
	std::vector<int>& arr = page.data;
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		// Move elements of arr[0..i-1],
		// that are greater than key,
		// to one position ahead of their
		// current position
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

// Function for Selection sort
void selectionSort(Page& page, int n)
{
	std::vector<int>& arr = page.data;
	int i, j, min_idx;

	// One by one move boundary of
	// unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the minimum element in
		// unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}

		// Swap the found minimum element
		// with the first element
		if (min_idx != i){
			swap(arr[min_idx], arr[i]);
	}
	}
}

int partition(int arr[], int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}
 
		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}


int main(int argc, char* argv[]) {
    PagedArray memory;

    // Leer archivo de entrada
    std::ifstream inputFile(argv[2]);
    if (!inputFile) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::vector<int> inputArray;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string valueStr;
        while (std::getline(iss, valueStr, ',')) {
            int value = std::stoi(valueStr);
            inputArray.push_back(value);
        }
    }

    // Dividir y almacenar el arreglo en páginas
    std::vector<int> currentPage;
    for (size_t i = 0; i < inputArray.size(); ++i) {
        currentPage.push_back(inputArray[i]);

        if (currentPage.size() * sizeof(int) >= PAGE_SIZE || i == inputArray.size() - 1) {
            memory.storeArray(currentPage);
            currentPage.clear();
        }
    }
    if (argc >= 5) {
        if (strcmp(argv[4], "SS") == 0) {
            for (Page& page : memory.getPages()) {
                selectionSort(page, page.data.size());
            }
        } else if (strcmp(argv[4], "QS") == 0) {
            for (Page& page : memory.getPages()) {
                //quickSort(page.data., 0, page.data.size()-1);
            }
        } else if (strcmp(argv[4], "IS") == 0) {
            for (Page& page : memory.getPages()) {
                insertionSort(page, page.data.size());
            }
        } else if (strcmp(argv[4], "PS") == 0) {
            for (Page& page : memory.getPages()) {
                bubbleSort(page, page.data.size());
            }
        } else {
            cout << "Algoritmo de ordenamiento desconocido" << endl;
        }
    }


    // Guardar datos ordenados en un archivo
    std::ofstream outputFile(argv[6]);
    if (outputFile.is_open()) {
        for (const Page& page : memory.getPages()) {
            for (size_t i = 0; i < page.data.size(); ++i) {
                outputFile << page.data[i];
                if (i != page.data.size() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << ",";
        }

        outputFile.close();
        std::cout << "Datos ordenados guardados en datos_ordenados.txt" << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo datos_ordenados.txt para escritura." << std::endl;
    }

    return 0;
}