#include <bits/stdc++.h>
using namespace std;
/*
 * 只有90，不知道错哪儿了，懒得找了。。。。。。
struct ip_pre{
    int len;
    long long ip;
    ip_pre(int a, long long b){
        len = a;
        ip = b;
    }
    bool operator <(const ip_pre &c) const{
        long long a=ip<<(32-len);
        long long b=c.ip<<(32-c.len);
        if(a!=b) return a<b;
        return len<c.len;
    }
};
int get_num(string str,int s,int t){//取数
    int x=0;
    for(int i=s;i<t;i++)
        x=x*10+str[i]-'0';
    return x;
}
set<ip_pre> cidr;
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    cin.get();
    for(int i=0;i<n;++i) {
        string str;
        getline(cin, str);
        //从字符串中获取ip
        int l=0,s=0,t=str.find(".",0);
        long long temp=0;
        while(t!=string::npos){
            temp=(temp<<8)+get_num(str,s,t);//两个'.'之间表示八位二进制
            l+=8;//每存在一个'.'，len加8
            s=t+1;
            t=str.find(".",s);
        }
        l+=8;
        t=str.find("/",s);
        if(t!=string::npos){
            temp=(temp<<8)+get_num(str,s,t);
            temp=temp<<(32-l);//扩展为32位
            l=get_num(str,t+1,str.size());
            temp=temp>>(32-l);//留下前缀
        }
        else
            temp=(temp<<8)+get_num(str,s,str.size());
        ip_pre curr(l, temp);
        cidr.insert(curr);
    }
    //合并移除
    for(auto it=cidr.begin();it!=cidr.end();++it){
        auto it_next = it;
        it_next++;
        while(it_next!=cidr.end()){//从当前往后挨个比较合并
            long long curr_ip = it->ip, next_ip = it_next->ip;
            int t = it_next->len - it->len;
            if(t<0) break;
            next_ip = next_ip>>t;
            if(curr_ip==next_ip) cidr.erase(it_next++);
            else break;
        }
    }
    //进一步合并
    for(auto it=cidr.rbegin();it!=cidr.rend();it++){//逆序
        auto it_next=it;
        it_next++;
        while(it_next != cidr.rend()){//合并同长的ip前缀
            long long a=it->ip,b=it_next->ip;
            if(it->len==it_next->len && (a >> 1) == (b >> 1)){
                ip_pre add_ip(it->len-1, a>>1);
                cidr.insert(add_ip);
                cidr.erase(*it_next);
                cidr.erase(*it);
                it_next=it;//删除*it的时候，it后继的迭代器会失效，需要重新赋值
                it_next++;
            }
            else break;
        }
    }
    //输出
    for(auto it=cidr.begin();it!=cidr.end();it++){
        long long a=(*it).ip<<(32-(*it).len);
        int k=1<<24;
        cout<<a/k;
        for(int i=0;i<3;i++){
            a=a%k;
            k=k>>8;
            cout<<"."<<a/k;
        }
        cout<<"/"<<(*it).len<<endl;
    }
    return 0;
}
*/
//网上的满分，借鉴一下
#define ll long long
struct Point  //ip是这个ip地址的十进制表示，ABCD分别是四个数字。
{
    ll ip,A,B,C,D;//len是前缀长度
    int len;
}Ip[100005];
bool cmp(Point a,Point b){//先按照ip再按照长度排序
    if(a.ip==b.ip){
        return a.len<b.len;
    }
    else return a.ip<b.ip;
}
bool check(Point a,Point b)//检验a和b能否进行a包含b的合并
/*
 * 判断b是否为a的子集
 * */
{
    if(a.len>b.len) return 0;
    else{//判断长度到a前缀为止前缀是否相同
        if((a.ip>>(32-a.len))==(b.ip>>(32-a.len)))return 1;
        else return 0;
    }
}
bool check2(Point a,Point b)//判断是否a并b能够构成a前缀少一位的合并
/*
 * 同级合并
 * */
{
    if(a.len!=b.len) return 0;
    if((a.ip>>(32-a.len+1))!=(b.ip>>(32-a.len+1)))return 0;
    if((a.ip>>(32-a.len))%2!=0)return 0;//提取a的第len位是不是0
    if((b.ip>>(32-b.len))%2==1)return 1;//提取b的第len位是不是1
}
Point sb(Point x){//sb函数返回为x的前缀少一位也就是a并b
    Point ans;
    ans=x;ans.len--;
    return ans;
}
int main()
{
    int n;
    cin>>n;
    char C[100005];
    for(int i=1;i<=n;i++){
        cin>>C;
        int l=strlen(C),num_d=0,num_x=0;
        for(int j=0;j<l;j++){//判断是哪一种ip前缀
            if(C[j]=='.')num_d++;
            if(C[j]=='/')num_x++;
        }
        ll a=0,b=0,c=0,d=0,Len=0,cnt=0,now=0;//不ll会爆int
        for(int j=0;j<l;j++){
            if(C[j]=='/'){now=0;cnt=100;continue;}
            if(C[j]=='.'){now=0;cnt++;continue;}
            now=now*10;now+=(C[j]-'0');
            if(cnt==0)a=now;if(cnt==1)b=now;
            if(cnt==2)c=now;if(cnt==3)d=now;
            if(j==l-1)Len=now;
        }//当作256进制乘起来
        Ip[i].A=a;Ip[i].B=b;Ip[i].C=c;Ip[i].D=d;
        Ip[i].ip=d+256*c+256*256*b+256*256*256*a;
        if(num_x)Ip[i].len=Len;
        else Ip[i].len=(num_d+1)*8;

    }
    vector<Point>v1;
    sort(Ip+1,Ip+1+n,cmp);//排序
    for(int i=1;i<=n;i++){//第一步合并
        int cnt=1;
        while(check(Ip[i],Ip[i+cnt])){cnt++;}
        v1.push_back(Ip[i]);
        i=i+cnt-1;
    }
    int lll=v1.size();//第二部合并
    for(vector<Point>::iterator it=v1.begin();it!=v1.end()-1;it++)
    {
        if(check2((*it),(*(it+1)))){
            v1.erase(it+1);
            (*it)=sb((*it));
            if(it!=v1.begin())it-=2;//题目说如果合并成功要回到这次合并的上一个
            else it--;//如果合并成功但是前边没有了
        }
    }
    lll=v1.size();//开心输出
    for(int i=0;i<lll;i++){
        cout<<v1[i].A<<"."<<v1[i].B<<"."<<v1[i].C<<"."<<v1[i].D<<"/"<<v1[i].len<<endl;
    }

}
/*
 * 网上提供的测试点
8
101.6.6.0/24
101.6.6.128/25
101.6.6/23
101/8
1/32
101.6.6.0
101.6
1
5
255.23.24.25/32
125.6.6.0/24
192.168.0.0/16
32.32.32.32/32
101.6.6.0/24
*/