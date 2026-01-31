#include<iostream>
#include<vector>
using namespace std;

int buy_sell_stock(vector<int>arr,int n){
int mini=arr[0],profit=0;
for(int i=1;i<n;i++){
    int cost=arr[i]-mini;
    profit=max(profit,cost);
    mini=min(mini,arr[i]);
}
return profit;
}

int main(){
    vector<int> prices = {7, 1, 5, 3, 6, 4};
int profit = buy_sell_stock(prices, prices.size());
cout << "Max Profit = " << profit << endl;
return 0;
}