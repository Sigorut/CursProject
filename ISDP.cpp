#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;
int Mprak = 0, Cprak = 0;
struct Vertex
{
	int Data;
	Vertex* Left;
	Vertex* Right;
};

Vertex* ISPD(int l, int r, int A[]) {
	int m;
	if (l > r) return NULL;
	else {
		m = ((l + r) / 2);
		Vertex* p = new Vertex;
		p->Data = A[m];
		p->Left = ISPD(l, m - 1, A);
		p->Right = ISPD(m + 1, r, A);
		return p;
	}
}
void Leftright(Vertex* p) {
	if (p != NULL) {
		Leftright(p->Left);
		cout << p->Data << " ";
		Leftright(p->Right);
		
	}
}
void Updown(Vertex* p) {
	if (p != NULL) {
	    cout << p->Data << " ";
		Updown(p->Left);
		Updown(p->Right);
		
	}
}

int Size(Vertex* p) {
	int n;
	if (p == NULL) n = 0;
	else n = 1 + Size(p->Left) + Size(p->Right);
	return n;
}


int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else if (b > a) {
		return b;
	}
	else return a;
}

int Height(Vertex* p) {
	int h;
	if (p == NULL) h = 0;
	else h = 1 + max(Height(p->Left), Height(p->Right));
	return h;
}
int SumLength(Vertex* p, int L) {
	int s;
	if (p == NULL) s = 0;
	else s = L + SumLength(p->Left, L + 1) + SumLength(p->Right, L + 1);
	return s;
}
bool Tree(Vertex* p){
    if
    (p !=NULL && ((p->Left != NULL && (p->Data < p->Left->Data || !Tree(p->Left))) ||
    (p->Right != NULL && (p->Data >= p->Right->Data || !Tree(p->Right)))))
    {
       return false;
    }
   
return true;
}
int Checksum(Vertex* p) {
	int S;
	if (p == NULL) S = 0;
	else S = p->Data + Checksum(p->Left) + Checksum(p->Right);
	return S;
}
int K_Sort (int n)
{
	int i=2, j=0;
	while (i<=n) 
	{
		i*=2;
		j++;
	}
	j--;
	return j;
}
void ShellSort (int A[], int n) 
{
	int i, j, k, l, t;
	l=K_Sort(n);
	int K[l];
	K[0]=1;
	for (i=1; i<l; i++) 
		K[i]=K[i-1]*2+1;
	for (; l>0; l--) 
	{
		k=K[l-1];
		for (i=k; i<n; i++) 
		{
			t=A[i]; Mprak++;
			j=i-k;
			while (j>=0 && (Cprak++, t<A[j])) 
			{
				A[j+k]=A[j];
				Mprak++;
				j-=k;
			}
			A[j+k]=t; Mprak++;
		}
	}
}

bool Search(Vertex* p, int x){
    cout<<"Root = "<<p->Data<<endl;
while (p != NULL){
if (p->Data < x){ p = p->Right;
if(p== NULL) break;
    cout<<"Right = "<<p->Data<<endl;
}
else {
if (p->Data > x) {p = p->Left;
if(p==NULL) break;
    cout<<"Left = "<<p->Data<<endl;
}
else  break;
    }
}
if (p != NULL) return true;
else return false;
}


int main() {
	int n=12, A[n];
	int g=12;
	for (int i = 0; i < 12; i++) {
		A[i] = g;
		g--;
		cout<<A[i]<<" ";
	}
	cout<<"   - Massive"<<endl;
	ShellSort (A, n);
	Vertex* Root = ISPD(0, 11, A);

	Updown(Root);
	cout <<"   - Updown"<<endl;
    
    Leftright(Root);
    cout <<"   - LeftRight"<<endl;
    
	cout << "Tree's size : " << Size(Root) << endl;

	cout << "Tree's checksum : " << Checksum(Root) << endl;

	cout << "Tree's height : " << Height(Root) << endl;
	
	cout << "Tree? : " <<Tree(Root)<<endl;

	cout << "Tree's average length : " << (float)SumLength(Root, 1) / (float)Size(Root)<<endl;
	cout << "Search?:" << Search(Root,1)<<endl;	
	return 0;
}