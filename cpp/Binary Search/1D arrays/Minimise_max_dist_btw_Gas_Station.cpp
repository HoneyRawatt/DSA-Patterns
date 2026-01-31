#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// | Method                  | Time Complexity     | Space Complexity | Notes                |
// | ----------------------- | ------------------- | ---------------- | -------------------- |
// | Brute Force             | O(k·n)              | O(n)             | Slow for large `k`   |
// | Priority Queue (Greedy) | O(k·log(n))         | O(n)             | Faster and intuitive |
// | Binary Search (Optimal) | O(n·log(maxDiff/ε)) | O(1)             | Most efficient       |

/**
 * Brute-force approach:
 * Place one gas station at a time in the segment with the largest current sub-segment.
 */
long double minimise_max_dist_brute(vector<int>& stations, int k) {
    int n = stations.size();
    vector<int> gasCount(n - 1, 0); // gasCount[i] = number of extra stations between stations[i] and stations[i+1]

    for (int addedStations = 0; addedStations < k; ++addedStations) {
        long double maxSectionLength = -1;
        int maxSectionIndex = -1;

        for (int i = 0; i < n - 1; ++i) {
            long double segmentLength = stations[i + 1] - stations[i];
            long double section = segmentLength / (gasCount[i] + 1);

            if (section > maxSectionLength) {
                maxSectionLength = section;
                maxSectionIndex = i;
            }
        }

        gasCount[maxSectionIndex]++;
    }

    long double result = 0;
    for (int i = 0; i < n - 1; ++i) {
        long double segmentLength = stations[i + 1] - stations[i];
        long double section = segmentLength / (gasCount[i] + 1);
        result = max(result, section);
    }

    return result;
}


/**
 * Priority Queue (Greedy) approach:
 * Always split the longest current section.
 */
long double minimise_max_dist_better(vector<int>& stations, int k) {
    int n = stations.size();
    vector<int> gasCount(n - 1, 0); // Number of extra stations in each segment

    // Max-heap to track the largest segment
    // Each entry is: (segmentLength, index)
    priority_queue<pair<long double, int>> pq;

    for (int i = 0; i < n - 1; ++i) {
        long double segmentLength = stations[i + 1] - stations[i];
        pq.push({segmentLength, i});
    }

    for (int added = 0; added < k; ++added) {
        auto top = pq.top(); pq.pop();
        int idx = top.second;
        gasCount[idx]++;

        long double fullLength = stations[idx + 1] - stations[idx];
        long double newSegment = fullLength / (gasCount[idx] + 1);
        pq.push({newSegment, idx});
    }

    return pq.top().first;
}


/**
 * Helper for binary search approach:
 * Calculate how many gas stations are needed to ensure all segments are <= dist
 */
int requiredStations(long double dist, vector<int>& stations) {
    int count = 0;
    for (int i = 1; i < stations.size(); ++i) {
        long double segment = stations[i] - stations[i - 1];
        count += floor(segment / dist);
    }
    return count;
}

/**
 * Binary Search approach (Optimized):
 * Search the smallest possible max distance by adjusting the precision.
 */
long double minimiseMaxDistance_optimized(vector<int>& stations, int k) {
    int n = stations.size();
    long double low = 0;
    long double high = 0;

    for (int i = 0; i < n - 1; ++i) {
        high = max(high, (long double)(stations[i + 1] - stations[i]));
    }

    long double eps = 1e-6; // Precision
    while ((high - low) > eps) {
        long double mid = (low + high) / 2.0;
        if (requiredStations(mid, stations) > k)
            low = mid;
        else
            high = mid;
    }

    return high;
}

int main() {
    vector<int> stations = {1,2,3,4}; // Example positions of stations
    int k = 3; // Number of additional gas stations to add

    cout << fixed;
    cout.precision(6);

    cout << "Brute-force Result: " << minimise_max_dist_brute(stations, k) << endl;
    cout << "Priority Queue Result: " << minimise_max_dist_better(stations, k) << endl;
    cout << "Binary Search Optimized Result: " << minimiseMaxDistance_optimized(stations, k) << endl;

    return 0;
}
