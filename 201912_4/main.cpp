#include <bits/stdc++.h>
using namespace std;
int n, m, t, k;
vector<vector<int>> adjList;
vector<vector<int>> nodeList;
map<int, unordered_map<int, vector<int>>> taskQueue;//依次为更新时间 更新节点 节点主链

void send(int time, int node_num) {//发送给node_num节点的邻居们并判断是否更新,若更新则加入任务队列
    auto& currList = nodeList[node_num];
    for(const int& ele : adjList[node_num]) {//遍历每一个邻居的链
        auto& neignbor = nodeList[ele];
        if(neignbor.size()<currList.size()||
           (neignbor.size()==currList.size()&&neignbor.back()>currList.back())) {
            //判断邻居是否需要更新
            auto& task = taskQueue[time+t][ele];
            if(task.empty()||task.size()<currList.size()||
               (task.size()==currList.size()&&task.back()>currList.back())) {
                //同一时间同一节点的任务则选择最优的
                task = currList;
            }
        }
    }
}
void update() { //执行任务
    int time = taskQueue.begin()->first;
    for (const auto& x : taskQueue[time]) {
        int node_num = x.first;
        auto& updateList = x.second;
        auto& currList = nodeList[node_num];
        if(currList.size()<updateList.size()||
           (currList.size()==updateList.size()&&currList.back()>updateList.back())) {
            currList = updateList;
            send(time, node_num);
        }
    }
    taskQueue.erase(time);
}
void executeCommands(const vector<vector<int>>& commands) {
    for(int i=0;i<k;++i) {
        int node_num = commands[i][0], time = commands[i][1];
        while(!taskQueue.empty()&&time>=taskQueue.begin()->first) {//若任务队列中有历史任务则执行之
            update();
        }
        if(commands[i].size()==2) {//查询命令
            cout << nodeList[node_num].size();
            for(auto& ele : nodeList[node_num]) {
                cout << " " << ele;
            }
            cout << endl;
        }
        else if(commands[i].size()==3) {//产生块命令
            int new_num = commands[i][2];
            nodeList[node_num].push_back(new_num);
            send(time, node_num);
        }
    }
}
//#define DEBUG
int main() {
#ifdef DEBUG
    fstream cin("input.txt");
#endif // DEBUG
    //ios::sync_with_stdio(false);
    cin >> n >> m;
    adjList.resize(502);
    nodeList.resize(n+1, { 0 });
    for(int i=0;i<m;++i) {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    cin >> t >> k;
    //cout << "action: " << k << endl;
    vector<vector<int>> commands;
    cin.get();//读取回车
    for(int i=0;i<k;++i){
        stringstream strs;
        string str;
        getline(cin, str);
        strs << str;
        int x;
        vector<int> temp;
        while (strs >> x) {
            temp.push_back(x);
        }
        commands.push_back(temp);
    }
    executeCommands(commands);
    return 0;
}
