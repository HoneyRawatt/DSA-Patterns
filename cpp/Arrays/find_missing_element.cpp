#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int missingele_XOR(vector<int>&a,int n){
    int xor1=0,xor2=0;
    for(int i=0;i<n;i++){
        xor2^=a[i];
        xor1^=(i+1);
    }
    xor1^=n+1;
    return xor1^xor2;
}
int missingele_sum(vector<int>&a,int n){
    int sum= ((n+1)*(n+2))/2;
    int asum=0;
    for(int i=0;i<n;i++){
        asum+=a[i];
    }
    return sum-asum;
}
int missingele_brute(vector<int>&a,int n){
    for(int i=1;i<=n+1;i++){
        int flag=0;
        for(int j=0;j<n;j++){
            if(a[j]==i){
                flag=1;
                break;
            }
        }if(flag==0) return i;
    }
    return -1;
}

int missingele_hashing(vector<int>&a,int n){
    int hash[n+2]={0};
    for(int i=0;i<n;i++){
        hash[a[i]]=1;
    }
    for(int i=1;i<=n+1;i++){
        if(hash[i]==0) return i;
    }
    return -1;
}
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Missing Element using XOR: " << missingele_XOR(arr, n) << endl;
    cout << "Missing Element using SUM: " << missingele_sum(arr, n) << endl;
    cout << "Missing Element using BRUTE: " << missingele_brute(arr, n) << endl;
    cout << "Missing Element using HASHING: " << missingele_hashing(arr, n) << endl;

    return 0;
}
