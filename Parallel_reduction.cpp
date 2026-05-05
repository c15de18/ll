#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

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

// -------------------- SEQUENTIAL FUNCTIONS --------------------
int sum_seq(const vector<int>& arr) {
    int total = 0;
    for (int x : arr) total += x;
    return total;
}

double average_seq(const vector<int>& arr) {
    int total = 0;
    for (int x : arr) total += x;
    return (double)total / arr.size();
}

int maximum_seq(const vector<int>& arr) {
    int max_value = arr[0];
    for (int x : arr) {
        if (x > max_value) max_value = x;
    }
    return max_value;
}

int minimum_seq(const vector<int>& arr) {
    int min_value = arr[0];
    for (int x : arr) {
        if (x < min_value) min_value = x;
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

    cout << "\n---- SEQUENTIAL EXECUTION ----\n\n";

    auto start = high_resolution_clock::now();
    int s1 = sum_seq(arr);
    auto end = high_resolution_clock::now();
    double t1 = duration<double, milli>(end - start).count();
    cout << "Sum: " << s1 << "\nTime: " << t1 << " ms\n\n";

    start = high_resolution_clock::now();
    double a1 = average_seq(arr);
    end = high_resolution_clock::now();
    double t2 = duration<double, milli>(end - start).count();
    cout << "Average: " << a1 << "\nTime: " << t2 << " ms\n\n";

    start = high_resolution_clock::now();
    int max1 = maximum_seq(arr);
    end = high_resolution_clock::now();
    double t3 = duration<double, milli>(end - start).count();
    cout << "Max: " << max1 << "\nTime: " << t3 << " ms\n\n";

    start = high_resolution_clock::now();
    int min1 = minimum_seq(arr);
    end = high_resolution_clock::now();
    double t4 = duration<double, milli>(end - start).count();
    cout << "Min: " << min1 << "\nTime: " << t4 << " ms\n\n";

    cout << "---- PARALLEL EXECUTION ----\n\n";

    start = high_resolution_clock::now();
    int s2 = sum_p(arr);
    end = high_resolution_clock::now();
    double tp1 = duration<double, milli>(end - start).count();
    cout << "Sum: " << s2 << "\nTime: " << tp1 << " ms\n";
    cout << "Speedup: " << (tp1 > 0 ? t1 / tp1 : 0) << "\n\n";

    start = high_resolution_clock::now();
    double a2 = average_p(arr);
    end = high_resolution_clock::now();
    double tp2 = duration<double, milli>(end - start).count();
    cout << "Average: " << a2 << "\nTime: " << tp2 << " ms\n";
    cout << "Speedup: " << (tp2 > 0 ? t2 / tp2 : 0) << "\n\n";

    start = high_resolution_clock::now();
    int max2 = maximum_p(arr);
    end = high_resolution_clock::now();
    double tp3 = duration<double, milli>(end - start).count();
    cout << "Max: " << max2 << "\nTime: " << tp3 << " ms\n";
    cout << "Speedup: " << (tp3 > 0 ? t3 / tp3 : 0) << "\n\n";

    start = high_resolution_clock::now();
    int min2 = minimum_p(arr);
    end = high_resolution_clock::now();
    double tp4 = duration<double, milli>(end - start).count();
    cout << "Min: " << min2 << "\nTime: " << tp4 << " ms\n";
    cout << "Speedup: " << (tp4 > 0 ? t4 / tp4 : 0) << "\n\n";

    return 0;
}