#include <iostream>
#include <vector>
#include <thread>
#include <numeric> 
#include <functional> 
#include <mutex> 

std::mutex mtx; 

void partial_sum(const std::vector<int>& vec, int start, int end, long long& result) {
    long long sum = std::accumulate(vec.begin() + start, vec.begin() + end, 0LL);

    std::lock_guard<std::mutex> lock(mtx);
    result += sum;
}

int main() {
    const int VECTOR_SIZE = 1000000;
    std::vector<int> vec(VECTOR_SIZE, 1); 

    const int NUM_THREADS = 4;
    std::vector<std::thread> threads;
    long long total_sum = 0;
    int part_size = VECTOR_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * part_size;
        int end = (i == NUM_THREADS - 1) ? VECTOR_SIZE : start + part_size;
        threads.emplace_back(partial_sum, std::ref(vec), start, end, std::ref(total_sum));
    }

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Vektorin elementtien summa on: " << total_sum << std::endl;

    return 0;
}