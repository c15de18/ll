#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

// -------------------- MERGE FUNCTION --------------------
void merge(vector<int>& arr, int start, int mid, int end)
{
    vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);

    int i = 0, j = 0, k = start;

    while(i < left.size() && j < right.size())
    {
        if(left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while(i < left.size()) arr[k++] = left[i++];
    while(j < right.size()) arr[k++] = right[j++];
}

// -------------------- SEQUENTIAL MERGE SORT --------------------
void mergeSortSequential(vector<int>& arr, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        mergeSortSequential(arr, start, mid);
        mergeSortSequential(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

// -------------------- PARALLEL MERGE SORT --------------------
void mergeSortParallel(vector<int>& arr, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;

        #pragma omp task shared(arr)
        mergeSortParallel(arr, start, mid);

        #pragma omp task shared(arr)
        mergeSortParallel(arr, mid + 1, end);

        #pragma omp taskwait
        merge(arr, start, mid, end);
    }
}

// -------------------- PRINT FUNCTION --------------------
void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// -------------------- MAIN --------------------
int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    if(n <= 0)
    {
        cout << "Invalid input.\n";
        return 0;
    }

    vector<int> arr(n), original(n);

    cout << "Enter elements:\n";
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
        original[i] = arr[i];
    }

    // -------------------- SEQUENTIAL --------------------
    auto start = high_resolution_clock::now();
    mergeSortSequential(arr, 0, n - 1);
    auto end = high_resolution_clock::now();

    double seqTime = duration<double, milli>(end - start).count();

    cout << "\nSequential Sorted Array: ";
    printArray(arr);
    cout << "Sequential Time: " << seqTime << " ms\n";

    // -------------------- PARALLEL --------------------
    arr = original;

    start = high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        mergeSortParallel(arr, 0, n - 1);
    }

    end = high_resolution_clock::now();

    double parTime = duration<double, milli>(end - start).count();

    cout << "\nParallel Sorted Array: ";
    printArray(arr);
    cout << "Parallel Time: " << parTime << " ms\n";

    // -------------------- SPEEDUP --------------------
    if (parTime > 0)
        cout << "\nSpeedup: " << seqTime / parTime << endl;
    else
        cout << "\nSpeedup: Undefined\n";

    return 0;
}