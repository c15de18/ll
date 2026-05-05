#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

// -------------------- PARALLEL FUNCTIONS --------------------
int sum_p(const vector<int>& arr) {
    int total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < (int)arr.size(); i++) {
        total += arr[i];
    }
    return total;
}

double average_p(const vector<int>& arr) {
    int total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < (int)arr.size(); i++) {
        total += arr[i];
    }
    return (double)total / arr.size();
}

int maximum_p(const vector<int>& arr) {
    int max_value = arr[0];
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

int minimum_p(const vector<int>& arr) {
    int min_value = arr[0];
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
}

// -------------------- MAIN --------------------
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid size.\n";
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\n---- RESULTS ----\n\n";

    int s = sum_p(arr);
    cout << "Sum: " << s << endl;

    double avg = average_p(arr);
    cout << "Average: " << avg << endl;

    int max_val = maximum_p(arr);
    cout << "Maximum: " << max_val << endl;

    int min_val = minimum_p(arr);
    cout << "Minimum: " << min_val << endl;

    return 0;
}