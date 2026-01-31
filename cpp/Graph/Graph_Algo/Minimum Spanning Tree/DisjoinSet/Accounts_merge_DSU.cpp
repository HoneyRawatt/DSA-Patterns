#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 DISJOINT SET UNION (Union-Find)
-----------------------------------------------------
Used to merge users (nodes) that share a common email.
*/
class DisjointSet {
public:
    vector<int> parent, size;

    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return;

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

/*
-----------------------------------------------------
⚡ mergeDetails(details)
-----------------------------------------------------
Each account:
details[i] = [name, email1, email2, ...]

If two accounts share an email, they belong to the same person.
We merge them using DSU and collect all unique emails per user.
-----------------------------------------------------
*/
vector<vector<string>> mergeDetails(vector<vector<string>>& details) {
    int n = details.size();
    DisjointSet ds(n);

    unordered_map<string, int> mapMailNode;  // email -> index of account

    // Step 1️⃣: Union accounts that share the same email
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < details[i].size(); j++) {
            string mail = details[i][j];
            if (mapMailNode.find(mail) == mapMailNode.end()) {
                mapMailNode[mail] = i;
            } else {
                ds.unionBySize(i, mapMailNode[mail]);
            }
        }
    }

    // Step 2️⃣: Group all emails by their ultimate parent (owner)
    vector<vector<string>> mergeMail(n);
    for (auto& it : mapMailNode) {
        string mail = it.first;
        int node = ds.findPar(it.second);
        mergeMail[node].push_back(mail);
    }

    // Step 3️⃣: Prepare final answer
    vector<vector<string>> ans;
    for (int i = 0; i < n; i++) {
        if (mergeMail[i].empty()) continue;
        sort(mergeMail[i].begin(), mergeMail[i].end());

        vector<string> temp;
        temp.push_back(details[i][0]);  // person name
        for (auto& mail : mergeMail[i]) {
            temp.push_back(mail);
        }
        ans.push_back(temp);
    }
    return ans;
}

/*
-----------------------------------------------------
🧭 main() – Example Dry Run
-----------------------------------------------------
Input:
[
  ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
  ["John", "johnsmith@mail.com", "john00@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]

Output:
[
  ["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnybravo@mail.com"]
]
*/
int main() {
    vector<vector<string>> details = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };

    vector<vector<string>> result = mergeDetails(details);

    cout << "Merged Accounts:\n";
    for (auto& acc : result) {
        for (auto& s : acc) cout << s << " ";
        cout << endl;
    }
    return 0;
}
// 🕒 Complexity
// Operation	           Time	        Space	    Notes
// Building DSU	           O(N)	        O(N)	     Initialize parent & size
// Union-Find Ops	      O(M × α(N))	O(M)	    M = total emails
// Sorting	              O(M log M)	O(M)	   per account’s merged emails
// Total	              O(M log M)	O(M + N)	practically linear