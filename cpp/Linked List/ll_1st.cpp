#include<iostream>
#include<vector>
using namespace std;

class node{
public:
     int data;
     node*next;
     node(int val){
        data=val;
        next=nullptr;
     }
};

int main(){
    vector<int>arr={2,5,0,7};
    node y= node(arr[0]);
    cout<<y.data<<endl;
    node *z= new node(arr[1]); 
    cout<<z->data<<endl;
}