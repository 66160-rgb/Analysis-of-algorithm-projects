#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int a1,d,S;
    cin>>a1>>d>>S;
    int A=d;
    int B=2*a1-d;
    int C=-2*S;
    int D=B*B-4*A*C;
    int n=(-B+sqrt(D))/(2*A);
    int last=a1+(n-1)*d;
    cout<<n<<" "<<last;
    return 0;
}