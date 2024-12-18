#pragma once
#include <vector>
#include <thread>

class PiCalculator {
public:
    PiCalculator(long long intervals, int threads);
    double calculate();
    double getExecutionTime() const;

private:
    double computeSegment(long long start, long long end);
    static void worker(PiCalculator* calculator, long long start, long long end, double& result);

    long long intervals_;
    int threads_;
    double executionTime_;
    std::vector<double> results_;
};


