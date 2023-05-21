#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;
char str[MAXN];

int sa[MAXN], sa_temp[MAXN];
int ra[MAXN], ra_temp[MAXN];
int c[MAXN];

int phi[MAXN];
int lcp[MAXN], plcp[MAXN];

int get_ra(int i, int k){
    if(sa[i] + k < n)
        return ra[sa[i] + k];
    return 0;
}

int count_sort(int k){
    memset(c, 0, sizeof(c));

    for(int i = 0; i < n; i++)
        c[get_ra(i, k)]++;

    int sum = 0, maxi = max(300, n);
    for(int i = 0; i < maxi; i++){
        int t = c[i];
        c[i] = sum, sum+= t;
    }

    for(int i = 0; i < n; i++)
        sa_temp[c[get_ra(i, k)]++] = sa[i];

    for(int i = 0; i < n; i++)
        sa[i] = sa_temp[i];
}

void fill_sa(){
    for(int i = 0; i < n; i++)
        ra[i] = str[i], sa[i] = i;

    for(int k = 1; k < n; k<<= 1){
        count_sort(k);
        count_sort(0);

        int curr = ra_temp[sa[0]] = 0;

        for(int i = 1; i < n; i++){
            if(get_ra(i, 0) == get_ra(i - 1, 0) && get_ra(i, k) == get_ra(i - 1, k))
                ra_temp[sa[i]] = curr;
            else
                ra_temp[sa[i]] = ++curr;
        }

        for(int i = 0; i < n; i++)
            ra[i] = ra_temp[i];
    }

    /*for(int i = 0; i < n; i++)
        cout<<sa[i]<<": "<<str + sa[i]<<"\n";
    cout<<"\n";*/
}

void fill_phi(){
    phi[sa[0]] = -1;
    for(int i = 1; i < n; i++)
        phi[sa[i]] = sa[i - 1];
}

void init(){
    cin >> str;
    n = strlen(str);
    str[n++] = '$';
    str[n] = '\0';

    fill_sa();
    fill_phi();
}

pair<int, int> _solve(){
    int s = *max_element(lcp, lcp + n);
    for(int i = 0; i < n; i++)
        if(lcp[i] == s) return {sa[i], s};
    return {-1, 0};
}

void solve(){
    int l = 0;
    for(int i = 0; i < n; i++){
        if(phi[i] == -1){
            plcp[i] = 0;
            continue ;
        }
        while(str[i + l] == str[phi[i] + l]) l++;
        plcp[i] = l;
        l = max(l - 1, 0);
    }

    for(int i = 0; i < n; i++)
        lcp[i] = plcp[sa[i]];//, cout<<sa[i]<<":\t"<<lcp[i]<<" "<<str + sa[i]<<"\n";
        //cout<<"\n";

    pair<int, int> s = _solve();
    cout<<s.first<<" - "<<s.second<<"\n";
    if(s.first == 0) cout<<"No repetitions found!\n";
    else{
        for(int i = s.first; i < s.first + s.second; i++)
            cout<<str[i];
        cout<<" "<<s.second<<"\n";
    }
}

int main(){
    int t;
    cin >> t;

    while(t--)
        init(), solve();
}
