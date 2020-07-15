#include <bits/stdc++.h>
using namespace std;
struct apple{
    int apple_num;
    bool drop;
};
vector<apple> tree;
int n, m, curr;
int T=0, D=0, E=0;

int main() {
    cin >> n;
    tree.resize(n);
    for(int i=0;i<n;++i){
        cin >> m;
        tree[i].drop = false;
        cin >> curr;
        tree[i].apple_num = curr;
        for(int j=1;j<m;++j){
            cin >> curr;
            if(curr>0) {
                if (tree[i].apple_num > curr) {
                    tree[i].apple_num = curr;
                    tree[i].drop = true;
                }
            } else {
                tree[i].apple_num += curr;
            }
        }
        if(tree[i].drop) D++;
        T += tree[i].apple_num;
    }
    if(tree[n-2].drop&&tree[n-1].drop&&tree[0].drop) E++;
    if(tree[n-1].drop&&tree[0].drop&&tree[1].drop) E++;
    for(int i=1;i<n-1;++i){
        if(tree[i-1].drop&&tree[i].drop&&tree[i+1].drop) E++;
    }
    cout << T << " " << D << " " << E << endl;
    return 0;
}
