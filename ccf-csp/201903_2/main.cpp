#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    string str;
    getchar();
    for(int i=0;i<n;++i){
        getline(cin, str);
        int ans = 0;
        //按运算符优先级分类讨论
        if(str[1]=='x'||str[1]=='/')//第一个运算符优先级高
        {
            if(str[1]=='x') ans = (str[0]-'0')*(str[2]-'0');
            else if(str[1]=='/') ans = (str[0]-'0')/(str[2]-'0');
            if(str[3]=='x'||str[3]=='/')//12都高
            {
                if(str[3]=='x') ans *= (str[4]-'0');
                else if(str[3]=='/') ans /= (str[4]-'0');
                //1高2高3高
                if(str[5]=='x') ans *= (str[6]-'0');
                else if(str[5]=='/') ans /= (str[6]-'0');
                //1高2高3低
                else if(str[5]=='+') ans += (str[6]-'0');
                else if(str[5]=='-') ans -= (str[6]-'0');
            }else{//1高2低再看三
                if(str[5]=='x'||str[5]=='/')//1高2低3高
                {
                    int three=0;
                    if(str[5]=='x') three = (str[4]-'0')*(str[6]-'0');
                    else if(str[5]=='/') three = (str[4]-'0')/(str[6]-'0');
                    if(str[3]=='+') ans += three;
                    else if(str[3]=='-') ans -= three;
                }else{//1高2低3低
                    if(str[3]=='+') ans += (str[4]-'0');
                    else if(str[3]=='-') ans -= (str[4]-'0');
                    if(str[5]=='+') ans += (str[6]-'0');
                    else if(str[5]=='-') ans -= (str[6]-'0');
                }
            }

        } else{//1低
            if(str[3]=='x'||str[3]=='/')//1低2高
            {
                if(str[3]=='x') ans = (str[2]-'0')*(str[4]-'0');
                else if(str[3]=='/') ans = (str[2]-'0')/(str[4]-'0');
                if(str[5]=='x'||str[5]=='/')//1低2高3高
                {
                    if(str[5]=='x') ans *= (str[6]-'0');
                    else if(str[5]=='/') ans /= (str[6]-'0');
                    if(str[1]=='+') ans += (str[0]-'0');
                    else if(str[1]=='-') ans = (str[0]-'0')-ans;
                }else{//1低2高3低
                    if(str[5]=='+') ans += (str[6]-'0');
                    else if(str[5]=='-') ans -= (str[6]-'0');
                    if(str[1]=='+') ans += (str[0]-'0');
                    else if(str[1]=='-') ans = (str[0]-'0')-ans;
                }
            } else{//12运算符都低
                if(str[1]=='+') ans += (str[0]-'0')+(str[2]-'0');
                else if(str[1]=='-') ans += (str[0]-'0')-(str[2]-'0');
                if(str[5]=='x'||str[5]=='/')//1低2低3高
                {
                    int three=0;
                    if(str[5]=='x') three = (str[4]-'0')*(str[6]-'0');
                    else if(str[5]=='/') three = (str[4]-'0')/(str[6]-'0');
                    if(str[3]=='+') ans += three;
                    else if(str[3]=='-') ans -= three;
                } else{//123都低
                    if(str[3]=='+') ans += (str[4]-'0');
                    else if(str[3]=='-') ans -= (str[4]-'0');
                    if(str[5]=='+') ans += (str[6]-'0');
                    else if(str[5]=='-') ans -= (str[6]-'0');
                }
            }
        }
        if(ans==24) printf("Yes\n");
        else printf({"No\n"});
    }
    return 0;
}
