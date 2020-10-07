#include <bits/stdc++.h>
using namespace std;
//直接模拟
struct signals{
    int kind;
    long long times;
    signals(){
        kind = 0;
        times = 0;
    }
};
long long r, y, g, n;
long long spend=0;
signals road[100005];
void change(int index, long long forward){//index号路口向前forward秒后的状态及剩余秒数
    if(road[index].kind==1){//当前红灯
        if(road[index].times>forward){//红灯走不完
            road[index].times -= forward;
        }else if(forward>=road[index].times&&forward<road[index].times+g){//红灯走完绿灯走不完
            road[index].kind = 3;
            road[index].times = g - (forward - road[index].times);
        }else if(forward>=road[index].times+g&&forward<road[index].times+g+y){//红灯走完绿灯走完黄灯没走完
            road[index].kind = 2;
            road[index].times = y - (forward - road[index].times - g);
        }else if(forward>=road[index].times+g+y&&forward<road[index].times+g+y+r){//走完一轮后
            road[index].kind = 1;
            road[index].times = r - (forward - road[index].times - g - y);
        }else if(forward>=r+g+y+road[index].times){
            forward = (forward-road[index].times)%(r+g+y);
            road[index].kind = 3;
            road[index].times = g;
            change(index, forward);
        }
    }else if(road[index].kind==2) {//同上
        if(road[index].times>forward){
            road[index].times -= forward;
        }else if(forward>=road[index].times&&forward<road[index].times+r){
            road[index].kind = 1;
            road[index].times = r - (forward - road[index].times);
        }else if(forward>=road[index].times+r&&forward<road[index].times+r+g){
            road[index].kind = 3;
            road[index].times = g - (forward - road[index].times - r);
        }else if(forward>=road[index].times+r+g&&forward<road[index].times+r+g+y){//走完一轮后
            road[index].kind = 2;
            road[index].times = y - (forward - road[index].times - r - g);
        }else if(forward>=r+g+y+road[index].times){
            forward = (forward-road[index].times)%(r+g+y);
            road[index].kind = 1;
            road[index].times = r;
            change(index, forward);
        }
    }else if(road[index].kind==3) {//同上
        if(road[index].times>forward){
            road[index].times -= forward;
        }else if(forward>=road[index].times&&forward<road[index].times+y){
            road[index].kind = 2;
            road[index].times = y - (forward - road[index].times);
        }else if(forward>=road[index].times+y&&forward<road[index].times+y+r){
            road[index].kind = 1;
            road[index].times = r - (forward - road[index].times - y);
        }else if(forward>=road[index].times+y+r&&forward<road[index].times+g+y+r){//走完一轮后
            road[index].kind = 3;
            road[index].times = g - (forward - road[index].times - y - r);
        }else if(forward>=r+g+y+road[index].times){
            forward = (forward-road[index].times)%(r+g+y);
            road[index].kind = 2;
            road[index].times = y;
            change(index, forward);
        }
    }
}

int main() {

    scanf("%lld %lld %lld %lld", &r, &y, &g, &n);
    for(int i=0;i<n;++i){
        scanf("%d %lld", &road[i].kind, &road[i].times);
    }
    for(int i=0;i<n;++i){
        cout << road[i].kind <<" "<< road[i].times <<endl;
        if(road[i].kind==0){
            spend += road[i].times;
            //更改后面的信号灯为road[i].times后
            change(i+1, spend);
        } else if(road[i].kind==1){
            spend += road[i].times;
            //更改后面的信号灯为road[i].times后
            change(i+1, spend);

        }else if(road[i].kind==2){
            spend += road[i].times + r;
            //更改后面的信号灯为road[i].times+r后
            change(i+1, spend);
        }
    }
    printf("%lld\n", spend);
    return 0;
}

/*
//短小精悍
int main()
{
    int r, y, g, n, k, t;
    long long ans = 0, tmp;
    scanf("%d%d%d%d", &r, &y, &g, &n);
    while(n--) {
        scanf("%d%d", &k, &t);

        if(k != 0) {
            if(k == 1)
                tmp = ans + (r - t);
            else if(k == 2)
                tmp = ans + r + g +y - t;
            else if(k == 3)
                tmp = ans + r + g - t;
            tmp %= r + g + y;

            if(tmp >= r + g)
                t = r + g + y + r - tmp;
            else if(tmp <= r)
                t = r - tmp;
            else
                t = 0;
        }
        ans += t;
    }

    printf("%lld", ans);

    return 0;
}
*/
/*
//测例
30 3 30
8
0 10
1 5
0 11
2 2
0 6
0 3
3 10
0 3

//调试信息
0 10
3 25
0 11
1 11
0 6
0 3
1 2
0 3
//输出
46
input：
30 3 30
8
0 50
1 20
0 11
2 2
0 50
0 25
3 10
0 3

outpu：
173
 * */