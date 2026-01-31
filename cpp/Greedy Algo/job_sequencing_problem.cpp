#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
🔹 PROBLEM: Job Sequencing Problem
======================================================================
Each job has:
  - id        → job number
  - deadline  → latest time it can be done
  - profit    → profit earned if completed before or on its deadline

Goal: Schedule jobs to maximize total profit.

We’ll show two approaches:
  1️⃣ Greedy (Simple Slot-based)
  2️⃣ Optimized Disjoint Set Union (DSU)
======================================================================
*/

// -------------------------------------------------------------
// 🧩 STRUCTURE DEFINITION
// -------------------------------------------------------------
struct Job {
    int id;
    int deadline;
    int profit;
};

// Comparison: sort jobs by profit descending
bool comp(Job a, Job b) {
    return a.profit > b.profit;
}

// -------------------------------------------------------------
// 🧩 GREEDY APPROACH
// -------------------------------------------------------------
/*
Approach (Greedy Slot Based):
--------------------------------
1️⃣ Sort jobs by profit (highest → lowest)
2️⃣ Create a slot array of size = max deadline
3️⃣ For each job:
       - Try to assign it to the latest free slot ≤ its deadline
4️⃣ Count number of jobs done and total profit.

🕒 Time Complexity:
    O(N log N + N * D)
    where D = maximum deadline
💾 Space Complexity:
    O(D)
*/
pair<int, int> maximum_profit(vector<Job>& arr) {
    sort(arr.begin(), arr.end(), comp);

    int maxd = 0;
    for (auto& job : arr)
        maxd = max(maxd, job.deadline);

    vector<int> slot(maxd + 1, -1); // slot[i] = job id occupying time i
    int totalProfit = 0, jobCount = 0;

    for (auto& job : arr) {
        for (int j = job.deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = job.id;
                totalProfit += job.profit;
                jobCount++;
                break;
            }
        }
    }
    return {jobCount, totalProfit};
}

// -------------------------------------------------------------
// 🧩 DISJOINT SET UNION (UNION-FIND) APPROACH
// -------------------------------------------------------------
/*
Approach (DSU Optimized):
--------------------------------
Instead of linearly searching for a free slot ≤ deadline,
we use a Disjoint Set Union (Union-Find) structure to
efficiently find and occupy slots.

Intuition:
---------
- Each slot points to the next available earlier slot.
- If slot ‘x’ is filled → we link it to slot ‘x-1’.
- The DSU `find()` helps us jump directly to the next
  available free slot in near O(1) time.

Steps:
------
1️⃣ Sort jobs by descending profit.
2️⃣ For each job, use DSU to find the latest available slot.
3️⃣ If available slot > 0, take it and merge(slot, slot-1).

🕒 Time Complexity: O(N log N + N * α(N)) ≈ O(N log N)
💾 Space Complexity: O(D)
*/
class DSU {
public:
    vector<int> parent;
    DSU(int n) { parent.resize(n + 1); for (int i = 0; i <= n; i++) parent[i] = i; }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int u, int v) {
        parent[u] = v; // occupy slot u → link to previous slot v
    }
};

pair<int, int> maximum_profit_DSU(vector<Job>& arr) {
    sort(arr.begin(), arr.end(), comp);

    int maxd = 0;
    for (auto& job : arr)
        maxd = max(maxd, job.deadline);

    DSU dsu(maxd);
    int totalProfit = 0, jobCount = 0;

    for (auto& job : arr) {
        int available = dsu.find(job.deadline);
        if (available > 0) {
            dsu.merge(available, available - 1);
            totalProfit += job.profit;
            jobCount++;
        }
    }
    return {jobCount, totalProfit};
}

// -------------------------------------------------------------
// 🧩 MAIN FUNCTION
// -------------------------------------------------------------
int main() {
    vector<Job> arr = {
        {1, 4, 20},
        {2, 1, 10},
        {3, 1, 40},
        {4, 1, 30}
    };

    // 🔸 Basic Greedy Approach
    auto result1 = maximum_profit(arr);
    cout << "🔹 Greedy Approach:\n";
    cout << "Jobs done: " << result1.first << endl;
    cout << "Total profit: " << result1.second << "\n\n";

    // 🔸 DSU Optimized Approach
    auto result2 = maximum_profit_DSU(arr);
    cout << "🔹 DSU Optimized Approach:\n";
    cout << "Jobs done: " << result2.first << endl;
    cout << "Total profit: " << result2.second << endl;

    return 0;
}

/*
======================================================================
🔹 INTUITION SUMMARY
======================================================================
- Both methods are based on the greedy idea:
  → Schedule the most profitable job first at the latest possible time.

- The **simple greedy** method checks each slot linearly,
  while the **DSU** method jumps directly to the next available slot.

✅ Example:
Jobs = [(1,4,20), (2,1,10), (3,1,40), (4,1,30)]
→ Sorted by profit = [3,4,1,2]
→ Max Profit = 60, Jobs Done = 2

🕒 Time Complexity:
  • Greedy: O(N log N + N * D)
  • DSU: O(N log N + N * α(N)) ≈ O(N log N)
💾 Space Complexity: O(D)

======================================================================
*/
