#include<iostream>
#include<vector>
using namespace std;
int removeDuplicateElements(vector<int>&a,int n){
    int i=0;
    for(int j=0; j<n; j++){
        if(a[i]!=a[j]){
            a[i+1]=a[j];
            i++;
        }
    }
    return i+1;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    cout<<"size of new array: "<<removeDuplicateElements(arr,n);
    return 0;
}