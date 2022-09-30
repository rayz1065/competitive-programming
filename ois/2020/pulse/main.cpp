#include <bits/stdc++.h>
#define MAXN 505
#define MAXP 150005
#define INFINITY (INT_MAX >> 1)
#define MAXR 7
#define MOD 60

using namespace std;

// bool mappa[MAXN][MAXN][MAXR];
bool is_map_scanned[MAXN][MAXN][MOD];
int dist[MAXN][MAXN][MOD];

int N, P;

int mov_x[] = {1, 0, -1, 0, 0},
    mov_y[] = {0, 1, 0, -1, 0};

int diag_x[] = {-1,  1,  1, -1},
    diag_y[] = {-1, -1,  1,  1};

int manhattan_dist(int x, int y, int x2, int y2){
    return abs(x2 - x) + abs(y2 - y);
}

/*bool is_scanned(int x, int y, int day){
    day%= MOD;
    return is_map_scanned[x][y][day];
}

void print_map_day(int day){
    day%= MOD;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout<<(is_map_scanned[i][j][day] ? 'o' : '-')<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    fflush(stdout);
}*/

bool in_range(int x, int y){
    return (x >= 0 && y >= 0 && x < N && y < N);
}

void place_radar(int x, int y, int r){
    for(int day = 0; day < MOD; day++){
        int curr_r = day%r;
        for(int m = 0; m < 4; m++){
            int i = x + mov_x[m] * curr_r,
                j = y + mov_y[m] * curr_r;

            while(manhattan_dist(x, y, i, j) == curr_r){
                if(in_range(i, j))
                    is_map_scanned[i][j][day] = true;
                i+= diag_x[m], j+= diag_y[m];
            }
        }

        if(curr_r > 0){
            curr_r--;
            for(int m = 0; m < 4; m++){
                int i = x + mov_x[m] * curr_r,
                    j = y + mov_y[m] * curr_r;

                while(manhattan_dist(x, y, i, j) == curr_r){
                    if(in_range(i, j))
                        is_map_scanned[i][j][day] = true;
                    i+= diag_x[m], j+= diag_y[m];
                }
            }
        }
    }
}

void init(){
    //fstream in;
    //in.open("input.txt", ios::in);

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> P;
    for(int i = 0; i < P; i++){
        int x, y, r;
        cin >> x >> y >> r;
        x--, y--;
        place_radar(x, y, r);
    }
}

struct node{
    int x;
    int y;
    int t;
};

int bfs(){
    for(int x = 0; x < N; x++){
        for(int y = 0; y < N; y++)
            fill(dist[x][y], dist[x][y] + MOD, INFINITY);
    }

    queue<node> ff;

    int x = 0, y = 0, t = 0;
    dist[x][y][t] = 0;
    ff.push({x, y, t});

    while(!ff.empty()){
        node curr_node = ff.front();
        ff.pop();

        x = curr_node.x, y = curr_node.y, t = curr_node.t;

        if(x == N - 1 && y == N - 1) return dist[x][y][t];

        for(int m = 0; m < 5; m++){
            int new_x = x + mov_x[m], new_y = y + mov_y[m], new_t = (t + 1)%MOD;
            if(in_range(new_x, new_y) && dist[x][y][t] + 1 < dist[new_x][new_y][new_t] && !is_map_scanned[new_x][new_y][new_t]){
                dist[new_x][new_y][new_t] = dist[x][y][t] + 1;
                ff.push({new_x, new_y, new_t});
            }
        }
    }
    return INFINITY;
}

int main(){
    init();

    cout<<bfs()<<"\n";
}











