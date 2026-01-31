#include<iostream>
using namespace std;

void pattern1(int n){
for(int i=0;i<n;i++){
    for(int j=0;j<i;j++)cout<<"*";
    cout<<endl;
}
}
void pattern2(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)cout<<j;
        cout<<endl;
    }
}
void pattern3(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)cout<<i;
        cout<<endl;
    }
}

void pattern4(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i+1;j++)cout<<"*";
        cout<<endl;
    }
}
void pattern5(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i+1;j++)cout<<j;
        cout<<endl;
    }
}

void pattern6(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i+1;j++)cout<<i;
        cout<<endl;
    }
}

void pattern7(int n){
    for(int i=0;i<n;i++){
        //spaces
        for(int j=0;j<n-i-1;j++)cout<<" ";
        //stars
        for(int j=0;j<=2*i;j++)cout<<"*";
        //spaces
        for(int j=0;j<n-i-1;j++)cout<<" ";
        cout<<endl;
    }
}
void pattern8(int n){
    for(int i=0;i<n;i++){
        //spaces
        for(int j=0;j<i;j++)cout<<" ";
        //stars
        for(int j=0;j<2*n-(2*i+1);j++)cout<<"*";
        //spaces
        for(int j=0;j<i;j++)cout<<" ";
        cout<<endl;
    }
}

void pattern9(int n){
    pattern7(n);
    pattern8(n);
}
void pattern10(int n){
    for(int i=1;i<=2*n-1;i++){
        int start=i;
        if(i>n) start=2*n-i;
        for(int j=1;j<=start;j++)cout<<"*";
        cout<<endl;
    }
}
void pattern11(int n){
    int start=1;
    for(int i=0;i<n;i++){
        if(i%2==0) start=1;
        else start=0;
        for(int j=0;j<=i;j++){
            cout<<start;
            start=1-start;
        }
        cout<<endl;
    }
}
void pattern12(int n){
    int space=2*(n-1);
    for(int i=1;i<=n;i++){
        //num
        for(int j=1;j<=i;j++)cout<<j;
        //spaces
        for(int j=1;j<=space;j++)cout<<" ";
        //num
        for(int j=i;j>=1;j--)cout<<j;
        cout<<endl;
        space-=2;
    }
}
void pattern13(int n){
    int num=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            cout<<num++;
        }
        cout<<endl;
    }
}

void pattern14(int n){
    for(int i=0;i<n;i++){
        for(char c='A';c<='A'+i;c++){
            cout<<c;
        }
        cout<<endl;
    }
}
void pattern15(int n){
    for(int i=0;i<n;i++){
        for(char c='A';c<='A'+(n-i-1);c++){
            cout<<c;
        }
        cout<<endl;
    }
}
void pattern16(int n){
    for(int i=0;i<n;i++){
         char c= 'A'+i;
        for(int j=0;j<=i;j++){
            cout<<c;
        }
        cout<<endl;
    }
}
void pattern17(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++) cout<<" ";
        char ch='A';
        int bp=(2*i+1)/2;
        for(int j=1;j<=2*i+1;j++){
            cout<<ch;
            if(j<=bp){ch++;}
            else{ch--;}
        }
        for(int j=0;j<n-i-1;j++) cout<<" ";
        cout<<endl;
    }
}
void pattern18(int n){
    for(int i=0;i<n;i++){
        char ch='A'+ (n-i);
        for(int j=0;j<=i;j++){
            cout <<ch;
            ch++;
        }
        cout<<endl;
    }
}
void pattern19(int n){
    int insidespace=0;
    for(int i=0;i<n;i++){
        //stars
        for(int j=1;j<=n-i;j++) cout<<"*";
        //spaces
        for(int j=1;j<=insidespace;j++) cout<<" ";
        //stars
        for(int j=1;j<=n-i;j++) cout<<"*";
        cout<<endl;
        insidespace+=2;
    }
    insidespace=2*n-2;
    for(int i=1;i<=n;i++){
        //stars
        for(int j=1;j<=i;j++) cout<<"*";
        //spaces
        for(int j=1;j<=insidespace;j++) cout<<" ";
        //stars
        for(int j=1;j<=i;j++) cout<<"*";
        insidespace-=2;
        cout<<endl;
    }
}
void pattern20(int n){
    int space=2*n-2;
    for(int i=1;i<=2*n-1;i++){
        int stars=i;
        if(i>n) stars=2*n-i;
        for(int j=1;j<=stars;j++)cout<<"*";
        for(int j=1;j<=space;j++)cout<<" ";
        for(int j=1;j<=stars;j++)cout<<"*";
        cout<<endl;
        if(i>=n)space+=2;
        else space-=2;
    }
}
void pattern21(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           if(i==0 || j==0 || i==n-1 || j==n-1) cout<<"*";
           else cout<<" ";
        }
        cout<<endl;
    }
}
void pattern22(int n){
    for(int i=0;i<2*n-1;i++){
        for(int j=0;j<2*n-1;j++){
         int top=i;
         int left=j;
         int right=(2*n-2)-j;
         int down=(2*n-2)-i;
         cout<<(n-min(min(top,down),min(left,right)));
        }
        cout<<endl;
    }
}
int main(){
int n;
cout<<"Enter the value of n: ";
cin>>n;
cout<<"\nPattern 1: "<<endl;
pattern1(n);
cout<<"\nPattern 2: "<<endl;
pattern2(n);
cout<<"\nPattern 3: "<<endl;
pattern3(n);
cout<<"\nPattern 4: "<<endl;
pattern4(n);
cout<<"\nPattern 5: "<<endl;
pattern5(n);
cout<<"\nPattern 6: "<<endl;
pattern6(n);
cout<<"\nPattern 7: "<<endl;
pattern7(n);
cout<<"\nPattern 8: "<<endl;
pattern8(n);
cout<<"\nPattern 9: "<<endl;
pattern9(n);
cout<<"\nPattern 10: "<<endl;
pattern10(n);
cout<<"\nPattern 11: "<<endl;
pattern11(n);
cout<<"\nPattern 12: "<<endl;
pattern12(n);
cout<<"\nPattern 13: "<<endl;
pattern13(n);
cout<<"\nPattern 14: "<<endl;
pattern14(n);
cout<<"\nPattern 15: "<<endl;
pattern15(n);
cout<<"\nPattern 16: "<<endl;
pattern16(n);
cout<<"\nPattern 17: "<<endl;
pattern17(n);
cout<<"\nPattern 18: "<<endl;
pattern18(n);
cout<<"\nPattern 19: "<<endl;
pattern19(n);
cout<<"\nPattern 20: "<<endl;
pattern20(n);
cout<<"\nPattern 21: "<<endl;
pattern21(n);
cout<<"\nPattern 22: "<<endl;
pattern22(n);
    return 0;
}