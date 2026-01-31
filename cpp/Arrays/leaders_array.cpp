#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

vector<int>superiorElement_brute(vector<int>&a){
    vector<int>ans;
    for(int i=0;i<a.size();i++){
        bool leader=true;
        for(int j=i+1;j<a.size();j++){
            if(a[j]>a[i]){
                leader=false;
                break;
            }
        }
        if(leader) ans.push_back(a[i]);
    }
    return ans;
}
vector<int> superiorElement(vector<int>&a){
    vector<int>ans;
    int maxi=INT_MIN;
    for(int i=a.size()-1;i>=0;i--){
        if(a[i]>maxi){
            ans.push_back(a[i]);
        }
        maxi=max(maxi,a[i]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}


int main() {
    vector<int> a = {1, 2, 3, 2, 1, 5, 3};
    vector<int> res = superiorElement(a);

    cout << "Superior elements are: ";
    for (int x : res) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
} 
