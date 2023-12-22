#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

int n;
int heights[MAXN];
vector<int> grafo[MAXN];
int gst[20][MAXN];
int lst[20][MAXN];
int dist[MAXN];

void buildGst(){
    for(int i = 0; i < n; i++)
        gst[0][i] = heights[i];

    for(int j = 1; j < 20; j++){
        int sz = 1 << j;
        for(int i = 0; i + sz - 1 < n; i++){
            gst[j][i] = max(gst[j - 1][i], gst[j - 1][i + (sz >> 1)]);
        }
    }
    /*for(int j = 1; j < 20; j++){
        int sz = 1 << j;
        for(int i = 0; i + sz - 1 < n; i++){
            cout<<gst[j][i]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";*/
}

void buildLst(){
    for(int i = 0; i < n; i++)
        lst[0][i] = heights[i];

    for(int j = 1; j < 20; j++){
        int sz = 1 << j;
        for(int i = 0; i + sz - 1 < n; i++){
            lst[j][i] = min(lst[j - 1][i], lst[j - 1][i + (sz >> 1)]);
        }
    }
    /* for(int j = 1; j < 20; j++){
        int sz = 1 << j;
        for(int i = 0; i + sz - 1 < n; i++){
            cout<<lst[j][i]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n"; */
}

int getLowest(int i, int j){
    int sz = j - i + 1;
    int gtexp2 = (31 - __builtin_clz(sz));

    //cout<<gtexp2<<" -> "<<i<<"|"<<j + 1 - (1<<gtexp2)<<"\n"<<lst[gtexp2][i]<<" "<<lst[gtexp2][j + 1 - (1<<gtexp2)]<<"\n";
    return min(lst[gtexp2][i], lst[gtexp2][j + 1 - (1<<gtexp2)]);
}

int getHeighest(int i, int j){
    int sz = j - i + 1;
    int gtexp2 = (31 - __builtin_clz(sz));

    //cout<<gtexp2<<" -> "<<i<<"|"<<j + 1 - (1<<gtexp2)<<"\n"<<lst[gtexp2][i]<<" "<<lst[gtexp2][j + 1 - (1<<gtexp2)]<<"\n";
    return max(gst[gtexp2][i], gst[gtexp2][j + 1 - (1<<gtexp2)]);
}

int findFirstGreatest(int i){
    int a = i + 1, b = n - 1;

    if(getHeighest(a, b) < heights[i])
        return i;

    while(b - a > 3){
        int m = (a + b) >> 1;
        if(getHeighest(a, m) >= heights[i])
            b = m;
        else
            a = m + 1;
    }

    for(int j = a; j <= b; j++){
        if(heights[j] >= heights[i])
            return j;
    }
    return i;
}

int findFirstLowest(int i){
    int a = i + 1, b = n - 1;

    if(getLowest(a, b) > heights[i])
        return i;

    while(b - a > 3){
        int m = (a + b) >> 1;
        if(getLowest(a, m) <= heights[i])
            b = m;
        else
            a = m + 1;
    }

    for(int j = a; j <= b; j++){
        if(heights[j] <= heights[i])
            return j;
    }
    return i;
}

int findLastGreatest(int i){
    int a = 0, b = i - 1;

    if(getHeighest(a, b) < heights[i])
        return i;

    while(b - a > 3){
        int m = (a + b) >> 1;
        if(getHeighest(m + 1, b) >= heights[i])
            a = m + 1;
        else
            b = m;
    }

    for(int j = b; j >= a; j--){
        if(heights[j] >= heights[i])
            return j;
    }
    return i;
}

int findLastLowest(int i){
    int a = 0, b = i - 1;

    if(getLowest(a, b) > heights[i])
        return i;

    while(b - a > 3){
        int m = (a + b) >> 1;
        if(getLowest(m + 1, b) <= heights[i])
            a = m + 1;
        else
            b = m;
    }

    for(int j = b; j >= a; j--){
        if(heights[j] <= heights[i])
            return j;
    }
}

void connectNodes(int i){
    grafo[i].push_back(i + 1);

    int a = findFirstGreatest(i);
    if(i != a)
        grafo[i].push_back(a);

    a = findFirstLowest(i);
    if(i != a)
        grafo[i].push_back(a);

    a = findLastLowest(i);
    if(i != a)
        grafo[a].push_back(i);

    a = findLastGreatest(i);
    if(i != a)
        grafo[a].push_back(i);
}

int bfs(){
    fill(dist, dist + n, INT_MAX >> 1);
    queue<int> ff;
    ff.push(0);
    dist[0] = 0;

    while(!ff.empty()){
        int curr = ff.front();
        ff.pop();

        for(auto i:grafo[curr]){
            if(dist[i] > dist[curr] + 1){
                dist[i] = dist[curr] + 1;
                ff.push(i);
            }

        }
    }
    return dist[n - 1];
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> heights[i];

    buildLst();
    buildGst();

    for(int i = 0; i < n; i++)
        connectNodes(i);

    cout<<bfs()<<"\n";
}
