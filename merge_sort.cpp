#include <iostream>
using namespace std;
void merge(int arr[],int l,int m,int r){
    int temp[100],i=l,j=m+1,k=0;
    while(i<=m && j<=r){
        if(arr[i]<arr[j]) temp[k++]=arr[i++];
        else temp[k++]=arr[j++];
    }
    while(i<=m) temp[k++]=arr[i++];
    while(j<=r) temp[k++]=arr[j++];
    for(i=l,k=0;i<=r;i++,k++) arr[i]=temp[k];
}
void mergesort(int arr[],int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
int main(){
    int arr[5]={5,3,8,1,2};
    mergesort(arr,0,4);
    for(int i=0;i<5;i++) cout<<arr[i]<<" ";
    return 0;
}