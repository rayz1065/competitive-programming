#include <fstream>
#include <iostream>

using namespace std;

struct info{int posx,posy,dir;};

int main(){
	fstream in,out;
	in.open("input.txt",ios::in);
	out.open("output.txt",ios::out);

	int N,M;
    in >> N >> M;
	info C[N+1];
    int Last[N];
	int l=N+10,pxi=0,pyi=0,di=1;

	int ax[]={0,1,0,-1};
	int ay[]={1,0,-1,0};
	char kom[N];

	for(int c=0;c<N;c++){
		in >> kom[c];
        C[c].posx=pxi;
		C[c].posy=pyi;
		C[c].dir=di;

		if(kom[c]=='F'){
			pxi+=ax[di];
			pyi+=ay[di];}
		else if(kom[c]=='B'){
			pxi-=ax[di];
			pyi-=ay[di];}
		else if(kom[c]=='R')
			di=(di+1)%4;
		else if(kom[c]=='L'){
			di=(di-1)%4;
			if(di<0)
                di+=4;}}

	C[N].posx=pxi;
    C[N].posy=pyi;
    C[N].dir=di;

    for(int c=N-1;c>=0;c--){
		if(kom[c]=='X')
			l=c;
		Last[c]=l;}



	int da,a,G;
	pxi=0,pyi=0,di=1;
    int Ncam[]={1,0,-1,0};
	int ANcam[]={0,1,0,-1};

	bool destroy=false;
	for(int c=0;c<M;c++){

		in >> da >> a;
        if(Last[da]<=a){
			a=Last[da];
			destroy=true;}//the lack follows

        G=di-C[da].dir;
        if(G<0)
            G+=4;

        pxi+=(C[a+1].posx-C[da].posx)*Ncam[(G)%4] + (C[a+1].posy-C[da].posy)*ANcam[(G)%4];
		pyi+=(C[a+1].posy-C[da].posy)*Ncam[(G)%4] + (C[a+1].posx-C[da].posx)*ANcam[(G+2)%4];
		di=(di+C[a+1].dir-C[da].dir)%4;
		if(di<0)
            di+=4;// devo cambiare!

		if(destroy){
			out << pxi << " " << pyi << endl;
			return 0;}}

	out << pxi << " " << pyi << endl;}
