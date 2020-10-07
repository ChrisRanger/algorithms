#include <iostream>
using namespace std;

int isSenevn(int x){
    int a, b, c;
    a = x - x/10*10;
    b = x/10 - x/100*10;
    c = x/100;
    if(x%7==0||a==7||b==7||c==7) {
        return 1;
    }
    else return 0;
}

int n;
int count[4] = {0};
bool A=true, B= false, C=false, D= false;
int main() {
    cin >> n;
    for(int i=1;i<=n;i++) {
        if (A) {
            count[0] += isSenevn(i);
            A = false;
            B = true;
        } else if (B) {
            count[1] += isSenevn(i);
            B = false;
            C = true;
        } else if (C) {
            count[2] += isSenevn(i);
            C = false;
            D = true;
        } else if (D) {
            count[3] += isSenevn(i);
            D = false;
            A = true;
        }
        n += isSenevn(i);
    }
    for(int i=0;i<4;i++){
        cout << count[i] << endl;
    }
    return 0;
}