#include "integral.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <mutex>

PiCalculator::PiCalculator(long long intervals, int threads) : intervals_(intervals), threads_(threads), executionTime_(0) {};

double PiCalculator::calculate() {
    results_.resize(threads_);
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;
    long long segment_size = intervals_ / threads_;
    for (int i = 0; i < threads_; ++i) {
        long long start = i * segment_size;
        long long end = (i == threads_ - 1) ? intervals_ : (i + 1) * segment_size;
        workers.emplace_back(worker, this, start, end, std::ref(results_[i]));
    }

    for (auto& thread : workers) {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    executionTime_ = elapsed.count();

    double total_sum = 0.0;
    for (double partial : results_) {
        total_sum += partial;
    }

    return total_sum * 4.0;
}

double PiCalculator::getExecutionTime() const {
    return executionTime_;
}

double PiCalculator::computeSegment(long long start, long long end) {
    double sum = 0.0;
    double step = 1.0 / intervals_;
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        sum += 1.0 / (1.0 + x * x);
    }
    return sum * step;
}

void PiCalculator::worker(PiCalculator* calculator, long long start, long long end, double& result) {
    result = calculator->computeSegment(start, end);
}
