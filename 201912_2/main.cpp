#include <iostream>
using namespace std;

int laji[1001][2];

int n, score[5]={0};

bool exist(int x, int y) {
    bool neighbor[4] = {false};
    for(int i=1;i<=n;i++) {
        if(laji[i][0]==x-1&&laji[i][1]==y) neighbor[0] = true;
        else if(laji[i][0]==x+1&&laji[i][1]==y) neighbor[1] = true;
        else if(laji[i][0]==x&&laji[i][1]==y-1) neighbor[2] = true;
        else if(laji[i][0]==x&&laji[i][1]==y+1) neighbor[3] = true;
    }
    return neighbor[0]&&neighbor[1]&&neighbor[2]&&neighbor[3];
}

int getScore(int x, int y) {
    int score=0;
    for(int i=1;i<=n;i++) {
        if(laji[i][0]==x-1&&laji[i][1]==y-1) score++;
        else if(laji[i][0]==x+1&&laji[i][1]==y+1) score++;
        else if(laji[i][0]==x-1&&laji[i][1]==y+1) score++;
        else if(laji[i][0]==x+1&&laji[i][1]==y-1) score++;
    }
    return score;
}

int main() {
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> laji[i][0] >> laji[i][1];
    }
    for(int i=1;i<=n;i++) {
        if(exist(laji[i][0], laji[i][1])) {
            if(getScore(laji[i][0], laji[i][1])==0) score[0]++;
            else if(getScore(laji[i][0], laji[i][1])==1) score[1]++;
            else if(getScore(laji[i][0], laji[i][1])==2) score[2]++;
            else if(getScore(laji[i][0], laji[i][1])==3) score[3]++;
            else if(getScore(laji[i][0], laji[i][1])==4) score[4]++;
        }
    }
    for(int i=0;i<5;i++) {
        cout << score[i] << endl;
    }

    return 0;
}
