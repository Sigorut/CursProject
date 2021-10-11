#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

struct Vertex
{
	int Data;
	Vertex* Left;
	Vertex* Right;
	int bal;
};

bool Rost;
bool HR = 1;
bool VR = 1;

void Btree(int D, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->Data = D;
		p->Left = p->Right = NULL;
		p->bal = 0;
		VR = 1;
	}
	else if(p->Data > D){
		Btree(D, p->Left);
		if (VR == 1) {
			if (p->bal == 0) {
				Vertex* q = p->Left;
				p->Left = q->Right;
				q->Right = p;
				p = q;
				q->bal = 1;
				VR = 0;
				HR = 1;
			}
			else {
				p->bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else {
			HR = 0;
		}
	}
	else if (p->Data < D) {
		Btree(D, p->Right);
		if (VR == 1) {
			p->bal = 1;
			VR = 0;
			HR = 1;
		}
		else if (HR == 1) {
			if (p->bal == 1) {
				Vertex* q = p->Right;
				p->bal = 0;
				q->bal = 0;
				p->Right = q->Left;
				q->Left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else {
				HR = 0;
			}
		}
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
int main() {
	srand(time(NULL));
	int i = 0, temp, j, k;
	Vertex* Root_1 = NULL;
	int A[100];
	for (i = 0; i < 12; i++) {
		while (true) {
			temp = rand() % 100;
			k = 0;
			for (j = 0; j < i; j++) {
				if (temp == A[j]) k++;
			}
			if (k == 0) {
				A[i] = temp;
				break;
			}
			else continue;
		}
	}
	for (i = 0; i < 12; i++) {
		cout << A[i] << " ";
		Btree(A[i], Root_1);
	}
	cout << endl;
	cout << endl;
	Insp(Root_1);
	cout << "\n\n";


	

	return 0;
}
