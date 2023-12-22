#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;

struct op{
    int figurine;
    bool removed;
};

vector<struct op> operazioni[MAXN];
int d[MAXN];
int x[MAXN];

int currentFigurines[MAXN];

// source: https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-12
struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex *segmentTrees[MAXN];

Vertex* build(int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}


void init(){
    cin >> n;
    string line;
    std::vector< std::vector<int> > dayOperations;
    dayOperations.push_back({});

    bool zeroAdded = false;
    getchar(); // endline

    // source: code adapted from https://stackoverflow.com/questions/2287121/how-to-read-groups-of-integers-from-a-file-line-by-line-in-c
    for(int day = 1; day <= n; day++){ // day is 1 bsed
        getline(cin, line);
        std::istringstream is( line );
        dayOperations.push_back(
                std::vector<int>( std::istream_iterator<int>(is),
                                  std::istream_iterator<int>() ) );
        for(auto j:dayOperations[day]){
            bool removed = j < 0;
            if(j == 0){
                if(zeroAdded)
                    removed = true;
                else
                    zeroAdded = true;
            }
            operazioni[day].push_back({abs(j), removed});
        }
    }

    for(int day = 1; day <= n; day++){
        cin >> d[day];
    }
}

int solve(){
    segmentTrees[0] = build(currentFigurines, 0, n - 1);
    for(int day = 1; day <= n; day++){ // days are 1 based
        Vertex *currentTree = segmentTrees[day - 1];
        for(auto j:operazioni[day]){
            // cout<<"day "<<day<<" add "<<j.figurine<<": "<<j.removed<<"\n";
            if(j.removed){
                currentTree = update(currentTree, 0, n - 1, j.figurine, 0);
            }
            else{
                currentTree = update(currentTree, 0, n - 1, j.figurine, 1);
            }
            // for(int i = 0; i < n; i++)
            //      cout<<i<<": "<<get_sum(currentTree, 0, n - 1, 0, i)<<"\n";
        }
        // cout<<"==============\n\n";

        segmentTrees[day] = currentTree;

        // cout<<"sum figurines up to "<<valueForX<<" -> "<<getSum(n + 255) - getSum(valueForX - 1)<<"\n";
        // cout<<"for day "<<day<<" x = "<<x[day]<<" "<<get_sum(segmentTrees[currentD], 0, n - 1, x[day - 1], n - 1)<<"\n";
    }

    for(int day = 1; day <= n; day++){
        int currentD = d[day];
        x[day] = (x[day - 1] + get_sum(segmentTrees[currentD], 0, n - 1, x[day - 1], n - 1))%n;
    }
    return x[n];
}

int main(){
    init();
    cout<<solve();
}
