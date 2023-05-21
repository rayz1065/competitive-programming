#include <bits/stdc++.h>
#define SIZE 1024
#define MAXQ (SIZE*4 + 10)
#define CHILD_NODE(x, j) ((x<<2) + j + 1)
#define ROOT_NODE 0

using namespace std;

char quadtree_a[MAXQ],
     quadtree_b[MAXQ],
     quadtree_s[MAXQ];

int _fill_quad_tree(char quadtree[], int k, string &q, int i){
    assert(0 <= k && k < MAXQ);
    quadtree[k] = q[i];

    if(q[i] == 'e' || q[i] == 'f'){
        i++;
    }
    else{
        assert(q[i] == 'p');
        i++;
        for(int j = 0; j < 4; j++){
            i = _fill_quad_tree(quadtree, CHILD_NODE(k, j), q, i);
        }
    }
    return i;
}

void fill_quad_tree(char quadtree[], string &q){
    _fill_quad_tree(quadtree, ROOT_NODE, q, 0);
}

int count_full(char q[], int k, int dim){
    assert(0 <= k && k < MAXQ);
    assert(dim >= 1);
    if(q[k] == 'f') return dim;
    if(q[k] == 'e') return 0;

    assert(q[k] == 'p');

    int s = 0;
    for(int j = 0; j < 4; j++){
        s+= count_full(q, CHILD_NODE(k, j), dim >> 2);
    }
    return s;
}

void init(){
    string q;

    fill(quadtree_a, quadtree_a + MAXQ, 'e');
    fill(quadtree_b, quadtree_b + MAXQ, 'e');

    cin >> q;
    fill_quad_tree(quadtree_a, q);
    cin >> q;
    fill_quad_tree(quadtree_b, q);
}

void copy_quadtree(char q[], char copy_to[], int k){
    assert(0 <= k && k < MAXQ);

    copy_to[k] = q[k];
    if(q[k] == 'p'){
        for(int j = 0; j < 4; j++){
            copy_quadtree(q, copy_to, CHILD_NODE(k, j));
        }
    }
}

void add_quadtree(char q1[], char q2[], char sum_q[], int k){
    assert(0 <= k && k < MAXQ);
    if(q1[k] == 'f' || q2[k] == 'f'){
        sum_q[k] = 'f';
    }
    else if(q1[k] == 'e' && q2[k] == 'e'){
        sum_q[k] = 'e';
    }
    else if(q1[k] == 'e'){
        copy_quadtree(q2, sum_q, k);
    }
    else if(q2[k] == 'e'){
        copy_quadtree(q1, sum_q, k);
    }
    else{
        sum_q[k] = 'p';
        for(int j = 0; j < 4; j++){
            add_quadtree(q1, q2, sum_q, CHILD_NODE(k, j));
        }
    }
}

int solve(){
    //copy_quadtree(quadtree_a, quadtree_s, ROOT_NODE);
    add_quadtree(quadtree_a, quadtree_b, quadtree_s, ROOT_NODE);
    return count_full(quadtree_s, ROOT_NODE, SIZE);
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    int N;
    cin >> N;

    while(N--){
        init();
        fprintf(out, "There are %d black pixels.\n", solve());
    }
}
