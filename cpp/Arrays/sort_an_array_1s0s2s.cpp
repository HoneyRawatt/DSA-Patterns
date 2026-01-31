#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
void sortarray_brute(vector<int>&arr,int n){
int cnt0=0,cnt1=0,cnt2=0;
for(int i=0;i<n;i++){
    if(arr[i]==0) cnt0++;
    else if(arr[i]==1) cnt1++;
    else cnt2++;
}
for(int i=0;i<cnt0;i++) arr[i]=0;
for(int i=cnt0; i<cnt0 + cnt1; i++) arr[i] = 1;
for(int i=cnt0 + cnt1; i<n; i++) arr[i] = 2;
}
void sortarray_dutch_national_flag_algo(vector<int>&arr,int n){
    int low=0,mid=0,high=n-1;
    while(mid<=high){
        if(arr[mid]==0){
            swap(arr[low],arr[mid]);
            low++,mid++;
        }else if(arr[mid]==1){
            mid++;
        }else{
            swap(arr[mid],arr[high]);
            high--;
        }
    }
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements (0s, 1s, and 2s): ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Original
    cout << "\nOriginal Array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Brute-force sorted copy
    vector<int> arr_brute = arr;
    sortarray_brute(arr_brute, n);
    cout << "\nSorted using Brute-force Counting:\n";
    for (int x : arr_brute) cout << x << " ";
    cout << endl;

    // Dutch National Flag
    vector<int> arr_dutch = arr;
    sortarray_dutch_national_flag_algo(arr_dutch, n);
    cout << "\nSorted using Dutch National Flag Algorithm:\n";
    for (int x : arr_dutch) cout << x << " ";
    cout << endl;

    return 0;
}