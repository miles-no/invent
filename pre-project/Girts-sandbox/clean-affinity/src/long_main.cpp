#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <algorithm>

using namespace std;

chrono::steady_clock::time_point getTime() {
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

void sleep(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

vector<int> allocateData(size_t size) {
    return vector<int>(size);
}


/**
 * An example of a function that takes a long time to execute.
 * Can be used for profiling.
 * @return 0 on success, 1 on failure.
 */
int main() {
    vector<int> data = allocateData(1000000);
    fillWithNumbers(data);

    auto start = getTime();

    sort(data);
    long long sum = sumElements(data);
    sleep(2);

    auto end = getTime();
    chrono::duration<double> elapsed = end - start;

    // Output the results
    cout << "Sum: " << sum << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}
