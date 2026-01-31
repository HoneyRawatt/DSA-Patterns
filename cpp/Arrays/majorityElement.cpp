#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int majorityElement_hashing(vector<int>arr){
map<int,int>mpp;
for(int i=0;i<arr.size();i++){
    mpp[arr[i]]++;
}
for(auto it:mpp){
    if(it.second > (arr.size()/2)){
        return it.first;
    }
}
return -1;
}

int majorityElement_moores_voting_algo(vector<int>arr){
    int cnt=0;
    int el;
    for(int i=0;i<arr.size();i++){
        if(cnt==0){
            cnt=1;
            el=arr[i];
        }else if(arr[i]==el){
            cnt++;
        }else{
            cnt--;
        }
    }
    int cnt1=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]==el) cnt1++;
    }
    if(cnt1>(arr.size()/2)){
        return el;
    }
    return -1;
}

int majorityElement_brute(vector<int>arr){
    for(int i=0;i<arr.size();i++){
            int cnt=0;
        for(int j=0;j<arr.size();j++){
            if(arr[i]==arr[j]){
                cnt++;
            }
        }
        if(cnt>(arr.size()/2)) return arr[i];
    }
    return -1;
}

int main() {
    vector<int> arr = {2, 2, 1, 2, 2, 3, 2};

    cout << "Majority using brute: " << majorityElement_brute(arr) << endl;
    cout << "Majority using hashing: " << majorityElement_hashing(arr) << endl;
    cout << "Majority using Moore's Voting: " << majorityElement_moores_voting_algo(arr) << endl;

    return 0;
}