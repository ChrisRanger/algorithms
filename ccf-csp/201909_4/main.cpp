#include <bits/stdc++.h>
using namespace std;
/*
int m, n, op_num;
struct good{//类别, 编号, 得分, 不参与推荐标志位(已被选过或本类商品已满)
    int cate, score, num;
    bool had;
};
vector <good> all_good;
bool cmp(good a, good b){
    if(!a.had) {
        if(!b.had){
            if(a.score==b.score) {
                if(a.cate==b.cate) return a.num<b.num;
                else return a.cate<b.cate;
            } else return a.score>b.score;
        }else return true;
    }
    else return false;
}
//#define DEBUG

int main(){
    scanf("%d %d", &m, &n);//m类各n个
    for(int i=0;i<n;++i){//读入商品信息
        int num, score;//编号,得分
        scanf("%d %d", &num, &score);
        for(int j=0;j<m;++j){
            good curr;
            curr.cate = j, curr.score = score, curr.had = false, curr.num = num;
            all_good.push_back(curr);
        }
    }
    scanf("%d", &op_num);//操作次数
    getchar();
    for(int i=0;i<op_num;++i){
        stringstream  strs;
        string str;
        getline(cin, str);
        strs << str;
        int x=0;
        vector<int> temp;
        while(strs >> x){
            temp.push_back(x);
        }
        if(temp[0]==1) {//加商品
            good add;
            add.had = false, add.cate = temp[1], add.num = temp[2], add.score = temp[3];
            all_good.push_back(add);//对应类增加该商品
#ifdef DEBUG
            cout << i <<  " add " << endl;
#endif
        }
        else if(temp[0]==2){//删商品
            auto itr = all_good.begin();
            while(itr!=all_good.end()){
                if(itr->cate==temp[1]&&itr->num==temp[2]){
                    itr = all_good.erase(itr);
                }
                else itr++;
            }
        }
        else if(temp[0]==3){//查询推荐
            vector<vector<int>> choosen;//选出商品的信息,每行一类
            choosen.resize(m);
            for(int x=0;x<temp[1];++x){//共选不超过k个
                sort(all_good.begin(), all_good.end(), cmp);//按既定规则将所有商品排序
                if(!all_good.front().had) {//推荐商品标志位正常
                    if(choosen[all_good.front().cate].size()<temp[all_good.front().cate+2]){//该类商品数量尚不够
#ifdef DEBUG
                        cout << i <<  " choosen: " << all_good.front().num << endl;
#endif
                        choosen[all_good.front().cate].push_back(all_good.front().num);//保存选中商品的信息
                        all_good.front().had = true;//该商品已选出则修改标志位重新排序继续选
                    }
                    else{//该类商品数量已满则修改该类所有商品标志位
                        int overnum = all_good.front().cate;
                        for(int q=0;q<all_good.size();++q){
                            if(all_good[q].cate==overnum) all_good[q].had = true;
                        }
                        x--;//当前没选,已选商品数量不增加,重来
                        continue;
                    }
                    //
                }else {//没有能选的了
                    break;;
                }
            }
            //输出
            for(int a=0;a<m;++a){
                if(choosen[a].empty()) printf("-1\n");//该类未选中商品则输出-1
                else {
                    sort(choosen[a].begin(), choosen[a].end());//同类商品按编号升序排列由小到大输出
                    printf("%d", choosen[a][0]);
                    for(int b=1;b<choosen[a].size();++b){
                        printf(" %d", choosen[a][b]);
                    }
                    printf("\n");
                }
            }
            for(int c=0;c<all_good.size();++c){
                all_good[c].had = false;
            }
        }

    }
    return 0;
}
以上代码本地测试样例可行,但是查询时多次排序,题目要求5s内,提交发现5.1s超时了,得用set或者map.....*/
struct Commodity{
    long long id,score;
    Commodity(long long id,long long score):id(id),score(score){}//构造函数
    //重载set的运算符，set里按该运算符进行排序
    bool operator <(const Commodity &c) const {
        return this->score!=c.score?this->score>c.score:this->id<c.id;
    }
};

int main(){
    long long m,n,op,id,score,k,c,t;
    cin>>m>>n;
    const long long mul=(long long)1e9;//用于hash

    vector<long long>K(m);//查询中每类物品挑选上限
    set<Commodity> commodities;//set存储商品信息自动排序
    unordered_map<long long, set<Commodity>::iterator>um;//可hash查找对应商品的迭代器,复杂度为常数

    for(int i=0;i<n;++i){
        cin>>id>>score;
        for(int j=0;j<m;++j){//读取所有商品信息,生成hash值存入unorder_map
            long long a=mul*j+id;//hash函数
            //set的insert返回的是pair，其中first是iterator
            um[a]=commodities.insert(Commodity(a,score)).first;
        }
    }

    cin>>op;
    while(op--){
        cin>>c;
        if(c==1){
            cin>>t>>id>>score;
            long long a=t*mul+id;
            um[a]=commodities.insert(Commodity(a,score)).first;
        }else if(c==2){
            cin>>t>>id;
            long long a=t*mul+id;
            commodities.erase(um[a]);//根据hash查到迭代器并删除,无需遍历查找
            um.erase(a);
        }else if(c==3){
            cin>>k;
            vector<vector<long long>>ans(m);//存推荐商品信息,一行一类
            for(int i=0;i<m;i++){
                cin>>K[i];//每类个数上限
            }
            for(auto &i:commodities){
                t=i.id/mul;//求得商品类型
                if(ans[t].size()<K[t]){//本类数量未达上限
                    ans[t].push_back(i.id%mul);//求得编号并存入
                    if(--k==0)//总数已满则结束推荐
                        break;
                }
            }
            //输出推荐结果
            for(auto&i:ans){//按行(类)遍历,为空则-1,否则输出编号
                if(i.empty()){
                    cout<<"-1";
                }else{
                    for(auto &j:i){//同类商品编号未排序且多输出了一个空格好像也没关系,排序了网上说反倒有问题....
                        cout<<j<<" ";
                    }
                }
                cout<<endl;
            }
        }
    }
    return 0;
}


/*
 3 100 1 1
1
1
1 0 4 3
1 0 5 1
3 10 2 2
1 4
-1
3 10 1 1
1
-1
2 0 1
3 2 1 1
4
-1
3 1 1 1
4
-1
 */