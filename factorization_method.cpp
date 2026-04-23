#include <iostream>
using namespace std;
int main(){
    int a1,d,S;
    cin>>a1>>d>>S;
    int sum=0,n=1;
    while(sum<S){
        sum+=a1+(n-1)*d;
        n++;
    }
    n--;
    int last=a1+(n-1)*d;
    cout<<n<<" "<<last;
    return 0;
}