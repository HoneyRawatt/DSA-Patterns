#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> intersection_array(vector<int>&a,vector<int>&b){
    vector<int>ans;
    int n1=a.size();
    int n2=b.size();
    int vis[n2]={0};
    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
        if(a[i]==b[j] && vis[j]==0){
            ans.push_back(b[j]);
            vis[j]=1;
            break;
        }
        if(b[j]>a[i]) break;
        } 
    }
    return ans;
}

vector<int>intersection_array2(vector<int>&a,vector<int>&b){
    int n=a.size();
    int i=0,j=0;
    vector<int>ans;
    while(i<n && j<n){
        if(a[i]<b[j]) i++;
        else if(b[j]<a[i]) j++;
        else{
            ans.push_back(a[i]);
            i++;
            j++;
        }
    }
    return ans; 
}
int main(){
    int n1,n2;
    cout<<"Enter the size of the arr1 and arr2: ";
    cin>>n1>>n2;
    vector<int>arr1(n1),arr2(n2);
    cout<<"Enter the elements arr1: ";
    for(int i=0;i<n1;++i){
        cin>>arr1[i];
    }
    cout<<"Enter the elements arr2: ";
    for(int i=0;i<n2;++i){
        cin>>arr2[i];
    }
    vector<int>unionarr=intersection_array(arr1,arr2);
    for(auto it: unionarr) cout<<it<<" ";

    return 0;
}