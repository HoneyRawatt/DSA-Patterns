#include<iostream>
#include<vector>
using namespace std;

int SecondlargestElement(vector<int>&arr,int n){
    int larg=arr[0];
    int seclarg= INT8_MIN;
    for(int i=0;i<n;i++){
        if(larg<arr[i]){
            seclarg=larg;
            larg=arr[i];
        }else if(arr[i]<larg && arr[i]>seclarg){
            seclarg=arr[i];
        }
    }
    return seclarg;
}
int SecondsmallestElement(vector<int>&a,int n){
    int small=a[0];
    int secsmall=INT8_MAX;
    for(int i=0;i<n;i++){
        if(small>a[i]){
            secsmall=small;
            small=a[i];
        }else if(a[i]!=small && secsmall<a[i]) secsmall=a[i];
    }
    return secsmall;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    cout<<"Second Largest Element: "<<SecondlargestElement(arr,n)<<endl;
    cout<<"Second Smallest Element: "<<SecondsmallestElement(arr,n)<<endl;
}