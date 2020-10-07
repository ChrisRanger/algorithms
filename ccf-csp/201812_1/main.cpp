#include <bits//stdc++.h>
using namespace std;

int main(){
    int r, y, g, n, spend = 0;
    scanf("%d %d %d %d", &r, &y, &g, &n);
    for(int i=0;i<n;++i){
        int k, t;
        scanf("%d %d", &k, &t);
        if(k==0){//路
            spend += t;
        }else if(k==1){//红灯
            spend += t;
        }else if(k==2){//黄灯
            spend += t + r;
        }else if(k==3){//绿灯

        }
    }
    printf("%d\n", spend);
    return 0;
}