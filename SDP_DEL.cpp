#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;



struct Vertex
{
	int Data;
	Vertex* Left;
	Vertex* Right;
};


void SDP_Req(int D, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->Data = D;
		p->Left = NULL;
		p->Right = NULL;
	}
	else if (D < p->Data) {
		SDP_Req(D, p->Left);
	}
	else if (D > p->Data) {
		SDP_Req(D, p->Right);
	}
}

void SDP_nReq(int D, Vertex*& Root_1) {
	Vertex** p = &Root_1;
	while ((*p) != NULL) {
		if (D < (*p)->Data)
			p = &((*p)->Left);
		else if (D > (*p)->Data) p = &((*p)->Right);
		else break;
	}

	if (*p == NULL) {
		(*p) = new Vertex;
		(*p)->Data = D;
		(*p)->Left = NULL;
		(*p)->Right = NULL;
	}
}

void DeleteVertex(int D, Vertex*& Root) {
	Vertex** p = &Root;
	Vertex* q, * r, * S;
	while (*p != NULL) {
		if (D < (*p)->Data)
			p = &((*p)->Left);
		else if (D > (*p)->Data)
			p = &((*p)->Right);
		else break;
	}

	if (*p != NULL) {
		q = *p;
		if (q->Left == NULL)
			* p = q->Right;
		else if (q->Right == NULL)
			* p = q->Left;
		else {
			r = q->Left;
			S = q;
			if (r->Right == NULL) {
				r->Right = q->Right;
				*p = r;
			}
			else {
				while (r->Right != NULL) {
					S = r;
					r = r->Right;
				}
				S->Right = r->Left;
				r->Left = q->Left;
				r->Right = q->Right;
				*p = r;
			}
		}
		delete(q);
	}
	else {
		cout << "ERROR: vertex doesn't exist" << endl;
	}

}

void Insp(Vertex* p) {
	if (p != NULL) {
		Insp(p->Left);
		cout << p->Data << " ";
		Insp(p->Right);
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


int Checksum(Vertex* p) {
	int S;
	if (p == NULL) S = 0;
	else S = p->Data + Checksum(p->Left) + Checksum(p->Right);
	return S;
}

bool Search(Vertex* p, int x){
    cout<<"Root = "<<p->Data<<endl;
while (p != NULL){
if (p->Data < x){ 
	p = p->Right;
	if(p== NULL) break;
	cout<<"Right = "<<p->Data<<endl;
}
else {
if (p->Data > x) {
	p = p->Left;
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
	srand(time(NULL));
	const int SIZE = 10;
	int A[]={ 23, 28, 5, 27, 68, 66, 20, 61, 69, 51  };

	Vertex* Root = NULL;
	Vertex* Root_1 = NULL;

	for (int i = 0; i < SIZE; i++) {
		SDP_Req(A[i], Root);
	}


	cout << endl;

	Insp(Root);
	cout << "\n\n";
	cout << endl;
	int h = Height(Root);
	int w = Size(Root);
	
	for (int j = 0; j < 11; j++) {
		int key;
		cout << endl << "Enter key delete: ";
		cin >> key;
		DeleteVertex(key, Root);
		Insp(Root);	
	}
	return 0;
}
