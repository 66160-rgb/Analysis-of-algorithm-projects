#include <iostream>
using namespace std;
int main() {
    int arr[10],count=0;
    for(int i=0;i<10;i++){
        cin>>arr[i];
        if(arr[i]%2==0) count++;
    }
    cout<<count;
    return 0;
}