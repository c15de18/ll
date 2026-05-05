#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {

        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void printArray(vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int N;

    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N), original(N);

    cout << "Enter elements:\n";
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        original[i] = arr[i];
    }

    auto start = chrono::high_resolution_clock::now();
    bubbleSortSequential(arr);
    auto end = chrono::high_resolution_clock::now();

    double seqTime = chrono::duration<double, milli>(end - start).count();

    cout << "\nSequential Sorted Array: ";
    printArray(arr);
    cout << "Sequential Time: " << seqTime << " ms\n";

    arr = original;

    start = chrono::high_resolution_clock::now();
    bubbleSortParallel(arr);
    end = chrono::high_resolution_clock::now();

    double parTime = chrono::duration<double, milli>(end - start).count();

    cout << "\nParallel Sorted Array: ";
    printArray(arr);
    cout << "Parallel Time: " << parTime << " ms\n";

    cout << "\nSpeedup: " << seqTime / parTime << endl;

    return 0;
}