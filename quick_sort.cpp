#include <iostream>
using namespace std;
void quick(int arr[],int l,int h){
    if(l<h){
        int p=arr[h],i=l-1;
        for(int j=l;j<h;j++){
            if(arr[j]<p){
                i++;swap(arr[i],arr[j]);
            }
        }
        swap(arr[i+1],arr[h]);
        int pi=i+1;
        quick(arr,l,pi-1);
        quick(arr,pi+1,h);
    }
}
int main(){
    int arr[5]={5,3,8,1,2};
    quick(arr,0,4);
    for(int i=0;i<5;i++) cout<<arr[i]<<" ";
    return 0;
}