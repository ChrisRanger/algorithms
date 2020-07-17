#include <bits/stdc++.h>
using namespace std;
vector<int> data;
int max_num, min_num, mid_num;
double mid_num1;
int main() {
    int n;
    scanf("%d", &n);
    data.resize(n);
    for (int i = 0; i < data.size(); ++i) {
        scanf("%d", &data[i]);
    }
    if (data.front() == data.back()) //全列相等或仅一个数
    {
        max_num = min_num = mid_num = data.front();
        cout << max_num << " " << mid_num << " " << min_num << endl;
    } else {
        if (data.front() < data.back()) {//降序
            max_num = data.back();
            min_num = data.front();
        } else {//升序
            max_num = data.front();
            min_num = data.back();
        }
        //找中位数
        if(data.size()%2==0){//偶数个
            mid_num1 = (data[data.size()/2-1]+data[data.size()/2])/2.0;
            //平均后仍为整数
            if(mid_num1==((int)mid_num1)) cout << max_num << " " << (int)mid_num1 << " " << min_num << endl;
            //为小数
            else{
                cout.setf(ios::fixed);
                cout<<setprecision(1);
                cout << max_num << " " << mid_num1 << " " << min_num << endl;
            }
        }
        else {//奇数个
            mid_num = data[(int)data.size()/2];
            cout << max_num << " " << mid_num << " " << min_num << endl;
        }
    }
    return 0;
}
