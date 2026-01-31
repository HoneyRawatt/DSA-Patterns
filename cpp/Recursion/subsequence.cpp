#include<iostream>
#include<vector>
using namespace std;

  /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - For each element, we have two choices:
        1) Pick the element
        2) Do NOT pick the element
    - We explore both choices using recursion.
    - When we reach index == n, one subsequence is formed.
    - This is a classic "Pick / Not Pick" recursion pattern.
    ====================================================
    */
void subseq(int ind,vector<int>&ds,int arr[],int n){
    if(ind==n){
        for(auto it:ds) cout<<it<<" ";
        if(ds.size()==0){
        cout<<"{}";}
    cout<<endl;
    return;
    }
    
    ds.push_back(arr[ind]);
    subseq(ind+1,ds,arr,n);
    ds.pop_back();
    subseq(ind+1,ds,arr,n);
}

int main(){
    int n=4;
    int arr[]={5,3,4,1};
    vector<int>ds;
    subseq(0,ds,arr,n);
}

// O(2^n)
// Each element has 2 choices (pick / not pick)
// Total subsequences = 2^n

// 📦 Space Complexity
// O(n)
// Recursive stack depth = n
// Temporary subsequence list (ds) can hold at most n elements

