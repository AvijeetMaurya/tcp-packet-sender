#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

inline void print_stats(std::vector<unsigned long long> cycles) {
    auto current = cycles.back();
    std::sort(cycles.begin(), cycles.end());
    auto n = cycles.size();
    auto total = std::accumulate(cycles.begin(), cycles.end(), 0ull);
    double mean = static_cast<double>(total) / n;
    auto min = *std::min_element(cycles.begin(), cycles.end());
    auto max = *std::max_element(cycles.begin(), cycles.end());
    std::transform(cycles.begin(), cycles.end(), cycles.begin(), [mean, n](double value){
        return ((value - mean)*(value - mean));
    });
    double std_dev = std::sqrt(std::accumulate(cycles.begin(), cycles.end(), 0.0) / n);
    std::cout << std::fixed << "Packets transmitted: " << n << "\nMean: " << mean << "\nMin: " << min << "\nMax: " << max << "\nCurrent: " << current << "\nstd-dev: " << std_dev << '\n';
}