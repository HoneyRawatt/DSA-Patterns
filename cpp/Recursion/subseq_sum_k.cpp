#include<bits/stdc++.h>
using namespace std;

int count_subseq_k(int ind,vector<int>&ds,int s,int arr[],int sum,int n){
if(ind==n){
    if(s==sum) return 1;
    else return 0;
}

s+=arr[ind];
int l= count_subseq_k(ind+1,ds,s,arr,sum,n);

s-=arr[ind];

int r= count_subseq_k(ind+1,ds,s,arr,sum,n);

return l+r;
}

// for one only
bool only_subseq_k(int ind,vector<int>&ds,int s,int arr[],int sum,int n){
if(ind==n){
    if(s==sum){
        for(auto it:ds) cout<<it<<" ";
        cout<<endl;
        return true;
    }
    else return false;
}
ds.push_back(arr[ind]);
s+=arr[ind];
if(only_subseq_k(ind+1,ds,s,arr,sum,n)) return true;
ds.pop_back();
s-=arr[ind];
if(only_subseq_k(ind+1,ds,s,arr,sum,n)) return true;

return false;
}

//for all
void subseq_k(int ind,vector<int>&ds,int s,int arr[],int sum,int n){
if(ind==n){
    if(s==sum){
        for(auto it:ds) cout<<it<<" ";
        cout<<endl;
    }
    return;
}
ds.push_back(arr[ind]);
s+=arr[ind];
subseq_k(ind+1,ds,s,arr,sum,n);
ds.pop_back();
s-=arr[ind];
subseq_k(ind+1,ds,s,arr,sum,n);
}

int main(){
    int n=4;
    int arr[]={5,3,4,1};
    int sum=4;
    vector<int>ds;
    subseq_k(0,ds,0,arr,sum,n);
}