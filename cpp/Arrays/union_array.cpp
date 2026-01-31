#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

// tc= O(n1logn1+ n2logn2)+ O(n1+n2)
vector<int>union_array1(vector<int>&a,vector<int>&b){
    set<int>st;
    for(int i=0;i<a.size();i++){
        st.insert(a[i]);
    }
    for(int i=0;i<b.size();i++){
        st.insert(b[i]);
    }
    vector<int>unionarr(st.size());
    int i=0;
    for(auto it:st) unionarr[i++]=it;

    return unionarr;
}

// tc=O(n1+n2)
vector<int>union_array(vector<int>&arr1,vector<int>&arr2){
    vector<int>unionarr;
    int n1=arr1.size(),n2=arr2.size();
    int i=0,j=0;
    while(i<n1 && j<n2 ){
        if(arr1[i]<=arr2[j]){
            if(unionarr.size()==0 || unionarr.back()!=arr1[i]){
                unionarr.push_back(arr1[i]);
            }
        i++;
        }else{
        if(unionarr.size()==0 || unionarr.back()!=arr2[j]){
                unionarr.push_back(arr2[j]);
            }
        j++;
        }
    }
    while(i<n1){
        if(unionarr.size()==0 || unionarr.back()!=arr1[i]){
                unionarr.push_back(arr1[i]);
        }
        i++;
    }
    while(j<n2){
        if(unionarr.size()==0 || unionarr.back()!=arr2[j]){
                unionarr.push_back(arr2[j]);
        }
        j++;   
    }
    return unionarr;
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
    vector<int>unionarr=union_array(arr1,arr2);
    for(auto it: unionarr) cout<<it<<" ";

    return 0;
}