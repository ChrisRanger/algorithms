#include <bits/stdc++.h>
using namespace std;
struct pixel{
    int rgb[3];
};
vector<vector<pixel>> picture;
vector<pixel> blocks;
int size_x, size_y, block_x, block_y;
string color;
int hex2ten(string hex){//两位十六进制字符转十进制数值
    int value = 0;
    if(hex[0]>='a'&&hex[0]<='z'){
        value = ((hex[0]-'a')+10)*16;
    } else if(hex[0]>='A'&&hex[0]<='Z'){
        value = ((hex[0]-'A')+10)*16;
    }
    else if(hex[0]>='0'&&hex[0]<='9'){
        value = (hex[0]-'0')*16;
    }
    if(hex[1]>='a'&&hex[1]<='z'){
        value += (hex[1]-'a')+10;
    } else if(hex[1]>='A'&&hex[1]<='Z'){
        value += (hex[1]-'A')+10;
    }
    else if(hex[1]>='0'&&hex[1]<='9'){
        value += hex[1]-'0';
    }
    return value;
}
pixel string2color(string s){
    pixel curr;
    if(s.size()==2){//若为#1类型,则扩充为两位十六进制字符,去掉#送入hex2ten函数
        s = s.insert(1, 1, '0');
        curr.rgb[0] = curr.rgb[1] = curr.rgb[2] = hex2ten(s.substr(1, 2));
    } else if(s.size()==4){//若为#111类型,则扩充为六位十六进制字符,分三次每两位送入hex2ten函数
        s = s.insert(1, 1, s[1]);
        s = s.insert(3, 1, s[3]);
        s = s.insert(5, 1, s[5]);
        curr.rgb[0] = hex2ten(s.substr(1, 2));
        curr.rgb[1] = hex2ten(s.substr(3, 4));
        curr.rgb[2] = hex2ten(s.substr(5, 6));
    } else if(s.size()==7){
        curr.rgb[0] = hex2ten(s.substr(1, 2));
        curr.rgb[1] = hex2ten(s.substr(3, 4));
        curr.rgb[2] = hex2ten(s.substr(5, 6));
    }
    return curr;
}
void printfColor(int rgb){//大于10的rgb值需按位以ASIC码输出
    int a = rgb/100, b = (rgb-a*100)/10, c = rgb - a*100 - b*10;
    if(a!=0) printf("\\x%X", a+48);
    if(a!=0||(a==0&&b!=0)) printf("\\x%X", b+48);
    printf("\\x%X", c+48);

}
int main() {
    cin >> size_x >> size_y >> block_x >> block_y;
    getchar();//吸收多余换行
    picture.resize(size_y);
    for(int i=0;i<size_y;++i){
        picture[i].resize(size_x);
        for(int j=0;j<size_x;++j){
            cin >> color;
            picture[i][j] = string2color(color);
        }
    }
    for(int i=0;i<size_y;i+=block_y){
        pixel now;
        for(int j=0;j<size_x;j+=block_x){
            int r=0, g=0, b=0;
            for(int m=0;m<block_y;++m){
                for(int n=0;n<block_x;++n){
                    r += picture[i+m][j+n].rgb[0];
                    g += picture[i+m][j+n].rgb[1];
                    b += picture[i+m][j+n].rgb[2];
                }
            }
            now.rgb[0] = r/(block_x*block_y);
            now.rgb[1] = g/(block_x*block_y);
            now.rgb[2] = b/(block_x*block_y);
            blocks.push_back(now);
        }
    }
    pixel before;
    before.rgb[0] = before.rgb[1] = before.rgb[2] = 0;
    for(int i=0;i<blocks.size();++i){
        if(blocks[i].rgb[0]==before.rgb[0]
           &&blocks[i].rgb[1]==before.rgb[1]
           &&blocks[i].rgb[2]==before.rgb[2]){//若当前色块和上一个色块rgb相同则无需改变颜色直接输出空格
            printf("\\x20");
        } else if(blocks[i].rgb[0]==0&&blocks[i].rgb[1]==0&&blocks[i].rgb[2]==0){//若当前色块和默认色相同则直接重置并输出空格
            printf("\\x1B\\x5B\\x30\\x6D\\x20");
            before.rgb[0] = before.rgb[1] = before.rgb[2] = 0;
        }
        else{//若颜色不同则更改rgb再输出空格
            printf("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B");
            printfColor(blocks[i].rgb[0]);
            printf("\\x3B");
            printfColor(blocks[i].rgb[1]);
            printf("\\x3B");
            printfColor(blocks[i].rgb[2]);
            printf("\\x6D\\x20");
            before.rgb[0] = blocks[i].rgb[0];
            before.rgb[1] = blocks[i].rgb[1];
            before.rgb[2] = blocks[i].rgb[2];
        }

        if((i+1)%(size_x/block_x)==0) {//每行结尾处
            if(before.rgb[0]!=0||before.rgb[1]!=0||before.rgb[2]!=0) {
                printf("\\x1B\\x5B\\x30\\x6D");//不是默认色则重置
                before.rgb[0] = before.rgb[1] = before.rgb[2] = 0;
            }
            printf("\\x0A");//每输出一行色块就输出一个换行符,共size_y/block_y个
        }
    }
    return 0;
}

/*
 测试样例2:
 2 2
 1 2
 #111111
 #0
 #000000
 #111
\x1B\x5B\x34\x38\x3B\x32\x3B\x38\x3B\x38\x3B\x38\x6D\x20\x20\x1B\x5B\x30\x6D\x0A
 */