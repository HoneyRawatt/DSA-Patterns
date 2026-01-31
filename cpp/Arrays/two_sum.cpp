#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
vector<int> two_sum_hashing(int n,vector<int>arr,int target){
map<int,int>map;
for(int i=0;i<n;i++){
    int num=arr[i];
    int more=target-num;
    if(map.find(more)!=map.end()){
        return {map[more],i};
    }
    map[num]=i;
}
return {-1,-1};
}

string two_sum_2pointer(int n, vector<int> arr, int target) {
    int left = 0, right = n - 1;
    sort(arr.begin(), arr.end());

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            return "YES";
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    return "NO";
}


vector<int>two_sum_brute(int n,vector<int>arr,int target){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(i==j) continue;
            if(arr[i]+arr[j]==target) return {i,j};
        }
    }
    return {-1,-1};
}
int main() {
    int n, k; 
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Enter target sum k: ";
    cin >> k;

    // Hashing Method
    vector<int> result = two_sum_hashing(n, arr, k);
    cout << "\nHashing Approach:\n";
    if (result[0] != -1) {
        cout << "Indices found: " << result[0] << " and " << result[1] << endl;
        cout << "Values: " << arr[result[0]] << " + " << arr[result[1]] << " = " << k << endl;
    } else {
        cout << "No valid pair found." << endl;
    }

    // Two-pointer (sorted)
    cout << "\nTwo-pointer Approach: " << two_sum_2pointer(n, arr, k) << endl;

    // Brute-force Method
    vector<int> brute = two_sum_brute(n, arr, k);
    cout << "\nBrute-force Approach:\n";
    if (brute[0] != -1) {
        cout << "Indices: " << brute[0] << " and " << brute[1] << endl;
        cout << "Values: " << arr[brute[0]] << " + " << arr[brute[1]] << " = " << k << endl;
    } else {
        cout << "No valid pair found." << endl;
    }

    return 0;
}
