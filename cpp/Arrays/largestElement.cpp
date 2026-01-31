#include<iostream>
#include<vector>
using namespace std;

int largestElement(vector<int>&arr,int n){
    int larg=arr[0];
    for(int i=0;i<n;i++){
        if(larg<arr[i]) larg=arr[i];
    }
    return larg;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    cout<<"Largest Element: "<<largestElement(arr,n)<<endl;
}