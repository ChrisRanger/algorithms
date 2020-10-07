#include <bits/stdc++.h>
using namespace std;
int len = 0;
bool recoverable;
int n;
char int2char(int num) {
    if (num > 9) return 'A' + num - 10;
    return '0' + num;
}
int char2int(char c) {
    if (c >= 'A') return c - 'A' + 10;
    return c - '0';
}
//x: disk id  y:  block id
string read(string *disks, int x, int y) {
    string res(8,'-');
    for (int i = 0; i < 8; i++) {
        int temp = 0;
        for (int j = 0; j < n; ++j) {
            if (j != x)
                temp ^= char2int(disks[j][i+y]);
        }
        res[i]=int2char(temp);
    }
    return res;
}
void recover(string *disks, int x, int y) {
    string &res = disks[x];
    if (res.length()==0) {
        if (!recoverable) {
            cout << '-' << endl;
            return;
        }
        cout << read(disks, x, y*8) << endl;
        return;
    }
    else if (y < len)
        cout << res.substr(y*8, 8) << endl;
    else {
        cout << '-' << endl;
        return;
    }
}
int main() {
    ios::sync_with_stdio(false);//没这句会超时。。。。
    int s, l;
    cin >> n >> s >> l;
    string disks[1024];
    for (int i = 0; i < l; ++i) {
        int index;
        cin >> index;
        cin>> disks[index];
        if (len == 0)
            len = (int)disks[index].length() / 8;
    }
    recoverable = l + 1 >= n;//缺失多于一块则无法恢复

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int b;
        cin >> b;
        int x = (b/s)% n;
        int y = (b / s) / (n - 1);//找位置，关键处
        y = y * s + (b%s);
        recover(disks, x, y);
    }

    return 0;
}
/*
 测试样例1：
 2 1 2
0 000102030405060710111213141516172021222324252627
1 000102030405060710111213141516172021222324252627
2
0
1
样例2：
3 2 2

0 000102030405060710111213141516172021222324252627
1 A0A1A2A3A4A5A6A7B0B1B2B3B4B5B6B7C0C1C2C3C4C5C6C7
2
2
5

 */