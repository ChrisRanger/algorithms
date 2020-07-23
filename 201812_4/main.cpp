#include <bits/stdc++.h>
using namespace std;
int coin[100001]={0};
int main() {
    int N, M;
    cin >> N >> M;
    for(int i=0;i<N;++i){
        int a;
        cin >> a;
        coin[a] = 1;
    }
    bool found = false;
    for(int i=1;i<M/2;++i){
        if(coin[i]==1&&coin[M-i]==1){
            cout << i << " " << M-i << endl;
            found = true;
            break;
        }
    }
    if(!found) cout << "No Solution" << endl;
    return 0;
}
