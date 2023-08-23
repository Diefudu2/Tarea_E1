#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

const int PAGE_SIZE = 1024;             // 1 KB
const int MAX_PAGES_IN_MEMORY = 6;

class Page {
public:
    std::vector<int> data;

    Page() {
        data.reserve(PAGE_SIZE / sizeof(int));
    }
};

class PagedArray {
private:
    std::vector<Page> memory;
    std::vector<int> loadedPages;
    int nextPageToReplace = 0; // Algoritmo de reemplazo: FIFO

public:
    PagedArray() {
        memory.resize(MAX_PAGES_IN_MEMORY);
    }

    int& operator[](size_t index) {
        int pageIndex = index / (PAGE_SIZE / sizeof(int));
        int pageOffset = index % (PAGE_SIZE / sizeof(int));

        if (std::find(loadedPages.begin(), loadedPages.end(), pageIndex) == loadedPages.end()) {
            loadPage(pageIndex);
        }

        return memory[pageIndex].data[pageOffset];
    }

    void loadPage(int pageIndex) {
        if (loadedPages.size() >= MAX_PAGES_IN_MEMORY) {
            replacePage();
        }

        loadedPages.push_back(pageIndex);
        // Simulate loading page data from disk
        for (int i = 0; i < PAGE_SIZE / sizeof(int); ++i) {
            memory[pageIndex].data.push_back(pageIndex * 1000 + i); // Simulated data
        }
    }

    void replacePage() {
        int pageToReplace = loadedPages[nextPageToReplace];
        nextPageToReplace = (nextPageToReplace + 1) % MAX_PAGES_IN_MEMORY;
        loadedPages.erase(std::remove(loadedPages.begin(), loadedPages.end(), pageToReplace), loadedPages.end());
        // Simulate unloading page data
        memory[pageToReplace].data.clear();
        std::cout << "Unloaded Page " << pageToReplace << " from memory.\n";
    }
};

// Quick Sort
void quickSort(PagedArray& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);

        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

int main() {
    int arrSize = 0;
    PagedArray arr;

    std::ifstream file("numbers.txt");
    if (!file) {
        std::cout << "Could not open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            arr[arrSize] = std::stoi(token);
            ++arrSize;
        }
    }

    quickSort(arr, 0, arrSize - 1);

    // Print sorted array
    for (int i = 0; i < arrSize; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}