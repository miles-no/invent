#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

using namespace std;

chrono::system_clock::time_point getTime() {
    return chrono::high_resolution_clock::now();
}

void fillWithNumbers(vector<int> &data) {
    iota(data.begin(), data.end(), 1);
}

void sort(vector<int> &data) {
    sort(data.begin(), data.end(), greater<>());
}

long long sumElements(vector<int> &data) {
    return accumulate(data.begin(), data.end(), 0LL);
}

void sleep(const int seconds) {
    // Busy loop for the specified number of seconds
    const auto startTime = getTime();
    const auto endTime = startTime + chrono::seconds(seconds);
    auto currentTime = startTime;
    while (currentTime < endTime) {
        currentTime = getTime();
    }
}

vector<int> allocateData(const size_t size) {
    return vector<int>(size);
}


/**
 * An example of a function that takes a long time to execute.
 * Can be used for profiling.
 *
 * @return Always returns zero.
 */
int main() {
    vector<int> data = allocateData(10000000);
    fillWithNumbers(data);

    const auto start = getTime();

    sort(data);
    const long long sum = sumElements(data);
    sleep(1);

    const auto end = getTime();
    const chrono::duration<double> elapsed = end - start;

    // Output the results
    cout << "Sum: " << sum << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}
