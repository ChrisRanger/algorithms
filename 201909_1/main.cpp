#include <bits/stdc++.h>
using namespace std;
int n, m;
struct apple{
    int nums;
    int shuguo_num;
};
vector<apple> all;
int T=0, k=-1, P=1;

int main() {
    scanf("%d %d", &n, &m);
    all.resize(n);
    for(int i=0;i<n;++i) {
        scanf("%d", &all[i].nums);//读初始苹果数
        all[i].shuguo_num = 0;
        for(int j=0;j<m;++j) {
            int curr = 0;
            scanf("%d", &curr);
            all[i].nums += curr;
            all[i].shuguo_num -= curr;
        }
        T += all[i].nums;
        if(all[i].shuguo_num>k) {
            k = all[i].shuguo_num;
            P = i + 1;
        }
    }
    printf("%d %d %d\n", T, P, k);
    return 0;
}
