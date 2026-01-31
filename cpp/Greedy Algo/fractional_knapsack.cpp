#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
💰 PROBLEM: Fractional Knapsack
------------------------------------------------------------
You are given:
  - A list of items, each with a value and a weight.
  - A knapsack with a maximum capacity `W`.

Goal:
  - Maximize the total value in the knapsack.
  - You can take *fractions* of an item (unlike 0/1 knapsack).
------------------------------------------------------------
*/

/* 
Structure to store value and weight of an item
*/
struct Item {
    int value;
    int weight;
};

/*
Comparator for sorting items by value/weight ratio in descending order
*/
bool comp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2; // higher ratio first
}

/*
------------------------------------------------------------
🔹 fractionalKnapsack FUNCTION
------------------------------------------------------------
Approach (Greedy):
1️⃣ Compute value-to-weight ratio for each item.
2️⃣ Sort items in descending order of this ratio.
3️⃣ Pick items one by one:
    - If it fits completely → take it all.
    - If not → take fractional part to fill remaining weight.
------------------------------------------------------------
Time Complexity:  O(N log N)  (due to sorting)
Space Complexity: O(1)
------------------------------------------------------------
*/
double fractionalKnapsack(vector<Item>& arr, int W) {
    sort(arr.begin(), arr.end(), comp); // sort by ratio descending

    double totalValue = 0.0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            // Take full item
            totalValue += arr[i].value;
            W -= arr[i].weight;
        } else {
            // Take fraction of item
            totalValue += (double)arr[i].value * ((double)W / arr[i].weight);
            break; // knapsack is full
        }
    }
    return totalValue;
}

/*
------------------------------------------------------------
🔹 MAIN FUNCTION
------------------------------------------------------------
*/
int main() {
    int W = 50; // Capacity of knapsack
    vector<Item> arr = {
        {60, 10},
        {100, 20},
        {120, 30}
    };

    double maxValue = fractionalKnapsack(arr, W);
    cout << "Maximum value in Knapsack = " << maxValue << endl;
    return 0;
}

/*
------------------------------------------------------------
🔹 INTUITION:
------------------------------------------------------------
- We take items with higher "value per weight" ratio first.
- Greedily fill knapsack until capacity is full.
- For the last item, take only the fraction that fits.

------------------------------------------------------------
🕒 Time Complexity:  O(N log N)
💾 Space Complexity: O(1)
------------------------------------------------------------
🔗 GFG Link:
https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
------------------------------------------------------------
*/
