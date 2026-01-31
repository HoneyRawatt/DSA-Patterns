#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>move_zero_at_end(vector<int>&arr,int n){
    vector<int>temp;
    for(int i=0;i<n;i++){
        if(arr[i]!=0) temp.push_back(arr[i]);
    }
    for(int i=0;i<temp.size();i++) arr[i]=temp[i];

    for(int i=temp.size();i<n;i++) arr[i]=0;

    return arr;
}
vector<int>move_zero_at_end2(vector<int>&arr,int n){
    int j=-1;
    //find the index of first 0
    for(int i=0;i<n;i++){
        if(arr[i]==0){
            j=i;
            break;
        }
    }
                
    // If no zero found
    if (j == -1) return arr;
    
    //shift the 0 to end 
    for(i=j+1;j<n;i++){
        if(arr[i]!=0){
            swap(arr[i],arr[j]);
            j++;
        }
    }
    return  arr;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    arr=move_zero_at_end2(arr,n);
    for(auto it: arr) cout<<it<<" ";
    return 0;
}