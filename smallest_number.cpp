#include <iostream>
using namespace std;
int main() {
    int a,b,c;
    cin>>a>>b>>c;
    int smallest=a;
    if(b<smallest) smallest=b;
    if(c<smallest) smallest=c;
    cout<<smallest;
    return 0;
}