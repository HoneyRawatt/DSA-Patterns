#include<iostream>
#include<vector>
using namespace std;

vector<int> rearrange_equal_brute(vector<int>arr,int n){
vector<int>pos,neg;
for(int i=0;i<n;i++){
    if(arr[i]>0){
        pos.push_back(arr[i]);
    }else neg.push_back(arr[i]);
}
for(int i=0;i<n/2;i++){
    arr[2*i]=pos[i];
    arr[2*i+1]=neg[i];
} 
return arr; 
}
vector<int> rearrange_equal(vector<int>arr,int n){
vector<int>ans(n,0);
int posindex=0,negindex=1;
for(int i=0;i<n;i++){
    if(arr[i]<0){
        ans[negindex]=arr[i];
        negindex+=2;
    }else{
        ans[posindex]=arr[i];
        posindex+=2;
    }
}
return ans;
}

vector<int> rearrange_unequal(vector<int>arr,int n){
vector<int>pos,neg;
for(int i=0;i<n;i++){
    if(arr[i]>0){
        pos.push_back(arr[i]);
    }else neg.push_back(arr[i]);
}
if(pos.size()>neg.size()){
    for(int i=0;i<neg.size();i++){
        arr[i*2]=pos[i];
        arr[i*2+1]=neg[i];
    }
    int index=neg.size()*2;
    for(int i=neg.size();i<pos.size();i++){
      arr[index]=pos[i];
      index++;
    }
}
else{
    for(int i=0;i<pos.size();i++){
        arr[i*2]=pos[i];
        arr[i*2+1]=neg[i];
    }
    int index=pos.size()*2;
    for(int i=pos.size();i<neg.size();i++){
      arr[index]=neg[i];
      index++;
    }
}
return arr;

}

int main() {
    // ✅ Test case for Equal count
    vector<int> equal_arr = {3, -1, -2, 4, -5, 6};  // 3 positive, 3 negative
    int n_equal = equal_arr.size();

    cout << "Equal Count Input: ";
    for (int x : equal_arr) cout << x << " ";
    cout << endl;

    vector<int> res1 = rearrange_equal_brute(equal_arr, n_equal);
    cout << "Equal Count (Brute): ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    vector<int> res2 = rearrange_equal(equal_arr, n_equal);
    cout << "Equal Count (Optimized): ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    cout << "\n-----------------------------\n";

    // ✅ Test case for Unequal count
    vector<int> unequal_arr = {3, -1, -2, 4, 5, 6, 7};  // 5 positive, 2 negative
    int n_unequal = unequal_arr.size();

    cout << "Unequal Count Input: ";
    for (int x : unequal_arr) cout << x << " ";
    cout << endl;

    vector<int> res3 = rearrange_unequal(unequal_arr, n_unequal);
    cout << "Unequal Count Rearranged: ";
    for (int x : res3) cout << x << " ";
    cout << endl;

    return 0;
}