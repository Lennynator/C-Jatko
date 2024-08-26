#include <iostream>
#include <vector>
#include <future> // std::async, std::future
#include <numeric> // std::accumulate

long long partial_sum(const std::vector<int>& vec, int start, int end) {
    return std::accumulate(vec.begin() + start, vec.begin() + end, 0LL);
}

int main() {
    const int VECTOR_SIZE = 1000000;
    std::vector<int> vec(VECTOR_SIZE, 1); 

    const int NUM_TASKS = 4;
    std::vector<std::future<long long>> futures;
    int part_size = VECTOR_SIZE / NUM_TASKS;

    for (int i = 0; i < NUM_TASKS; ++i) {
        int start = i * part_size;
        int end = (i == NUM_TASKS - 1) ? VECTOR_SIZE : start + part_size;
        futures.push_back(std::async(std::launch::async, partial_sum, std::ref(vec), start, end));
    }

    long long total_sum = 0;
    for (auto& fut : futures) {
        total_sum += fut.get(); 
    }

    std::cout << "Vektorin elementtien summa on: " << total_sum << std::endl;

    return 0;
}
