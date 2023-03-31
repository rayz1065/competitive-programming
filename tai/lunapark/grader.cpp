#include<bits/stdc++.h>
using namespace std;
int progetta(int N, int M, int K, vector<int> &A, vector<int> &B, vector<int> &W);
int main(){
	int N, M, K;
	cin>>N>>M>>K;
	vector<int> A(M), B(M), W(M);
	for(int i=0;i<M;i++)
		cin>>A[i]>>B[i]>>W[i];
	int score=progetta(N,M,K,A,B,W);
	cout<<score<<endl;
	return 0;
}
