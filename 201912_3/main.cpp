#include<iostream>
#include<unordered_map>
using namespace std;

//获取从s字符串开始的数字，并更新引用的索引指针startIndex，如果没有数字则返回默认值defaultValue
//注意不需要处理负数
int getNumberOrDefault(const string& s, int& startIndex, const int& defaultValue){
    int n = s.size(),retValue = 0;
    for(;startIndex<n;++startIndex){
        if(!isdigit(s[startIndex])) break;
        retValue = retValue*10 +(s[startIndex]-'0');
    }
    return retValue==0 ? defaultValue : retValue;
}
//处理 系数&化学式
void procExpressionUnit(unordered_map<string,int> &m, const string &s, const int& unit){
    //查找容器中是否插入过某元素
    unordered_map<string,int>::iterator it;

    int i=0,n=s.size();//循环起点和终点
    int base = unit * getNumberOrDefault(s,i,1);//当前化学式的系数
    int pNumber,pElement = i;//指向数字起始位置的指针和指向元素起始位置的指针

    while(i<n){
        if(isalpha(s[i])){//处理元素
            pElement=i;//记录元素起始位置
            if(i+1<n&&islower(s[1+i])) ++i;

            pNumber = ++i;//记录系数起始位置
            string strElement = s.substr(pElement,i-pElement);

            int entry_base = base;//该元素待计算的系数
            if(pNumber != n&&isdigit(s[i])){//如果有系数
                entry_base = base * getNumberOrDefault(s,i,1);//更新该元素系数 更新i
            }
            //以下将元素个数累加到容器中
            if((it=m.find(strElement))==m.end()){
                m.insert(pair<string,int>(strElement,entry_base));
            }
            else{
                it->second += entry_base;
            }
            continue;
        }
        if(s[i]=='('){//处理化学式
            //以下查找匹配的‘(’位置
            int countLeft = 1;
            pElement = ++i;
            for(;i<n;++i){
                if(s[i]=='(') ++countLeft;
                else if(s[i]==')') --countLeft;
                if(countLeft==0) break;
            }

            string strElement = s.substr(pElement,i-pElement);//化学式 也是项 紧跟着要处理其后的数字
            pNumber = ++i;//记录项后边数字的位置
            procExpressionUnit(m,strElement,base*getNumberOrDefault(s,pNumber,1));//处理这个化学式 并更新项的系数
            if(pNumber<n)//如果还有要处理的项
                procExpressionUnit(m,s.substr(pNumber,n-pNumber),base);
            return;
        }
    }
}
//处理表达式将表达式拆分成最小单位为：  系数&化学式
void procExpression(unordered_map<string,int> &m, const string &s){
    string sf = s+"+";
    int lastIndex = 0,currIndex = 0;
    while((currIndex = sf.find('+',currIndex))!=string::npos){
        procExpressionUnit(m,sf.substr(lastIndex,currIndex-lastIndex),1);
        lastIndex = ++currIndex;
    }
}
//判断字符串s是否是合法的化学方程式
bool isValidFormula(const string &s){
    //声明左右两边表达式容器：unordered_map<元素名，元素个数>
    unordered_map<string,int> leftExpression;
    unordered_map<string,int> rightExpression;
    //拆分并处理两边表达式
    int idx = s.find('=');
    procExpression(leftExpression,s.substr(0,idx));
    procExpression(rightExpression,s.substr(idx+1,s.size()-idx-1));
    //打印左右两边元素及其个数信息

    //开始判断两边表达式是否相等
    if(leftExpression.size()!=rightExpression.size()) return false;//第一层过滤，数量不等一定不合法
    for(unordered_map<string,int>::iterator itL = leftExpression.begin(),itR;itL!=leftExpression.end(); ++itL){//第二层过滤
        itR = rightExpression.find(itL->first);
        if(itR == rightExpression.end()) return false;//左边元素在右边元素中不存在
        if(itR->second!=itL->second) return false;//左边元素与右边元素数量不相等
    }
    return true;//不存在其他情况使两边表达式不等
}

int main(){
    int n;
    string s;
    cin>>n,getline(cin,s);//读取n，并去除这行的回车
    for(int i=0;i<n;++i){//不断读取行数据，做判断
        getline(cin,s);
        if(isValidFormula(s))
            cout<<"Y"<<endl;
        else
            cout<<"N"<<endl;
    }
    return 0;
}
