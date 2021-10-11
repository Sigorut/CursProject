//#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
using namespace std;

struct Vertex
{
	int Data;
	Vertex* Left;
	Vertex* Right;
	int bal;
};

bool Rost;
bool Less;

void LL_turn(Vertex*& p) {
	Vertex* q = p->Left;
	p->bal = 0;
	q->bal = 0;
	p->Left = q->Right;
	q->Right = p;
	p = q;
}

void RR_turn(Vertex*& p) {
	Vertex* q = p->Right;
	p->bal = 0;
	q->bal = 0;
	p->Right = q->Left;
	q->Left = p;
	p = q;
}

void LR_turn(Vertex*& p) {
	Vertex* q = p->Left;
	Vertex* r = q->Right;
	if (r->bal < 0)
		p->bal = 1;
	else p->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else q->bal = 0;
	r->bal = 0;
	q->Right = r->Left;
	p->Left = r->Right;
	r->Left = q;
	r->Right = p;
	p = r;
}

void RL_turn(Vertex*& p) {
	Vertex* q = p->Right;
	Vertex* r = q->Left;
	if (r->bal < 0)
		p->bal = 1;
	else p->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else q->bal = 0;
	r->bal = 0;
	q->Left = r->Right;
	p->Right = r->Left;
	r->Right = q;
	r->Left = p;
	p = r;
}

void AVL(int D, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->Data = D;
		p->Left = NULL;
		p->Right = NULL;
		p->bal = 0;
		Rost = true;
	}
	else if (p->Data > D) {
		AVL(D, p->Left);
		if (Rost == true) {
			if (p->bal > 0) {
				p->bal = 0;
				Rost = false;
			}
			else if (p->bal == 0) {
				p->bal = -1;
				Rost = true;
			}
			else if (p->Left->bal < 0) {
				LL_turn(p);
				Rost = false;
			}
			else {
				LR_turn(p);
				Rost = false;
			}
		}
	}
	else if (p->Data < D) {
		AVL(D, p->Right);
		if (Rost == true) {
			if (p->bal < 0) {
				p->bal = 0;
				Rost = false;
			}
			else if (p->bal == 0) {
				p->bal = 1;
				Rost = true;
			}
			else if (p->Right->bal > 0) {
				RR_turn(p);
				Rost = false;
			}
			else {
				RL_turn(p);
				Rost = false;
			}
		}
	}
	else {
	}
}
void RR1_turn(Vertex*& p) {
	Vertex* q = p->Right;
	if (q->bal == 0) {
		p->bal = 1;
		q->bal = -1;
		Less = false;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->Right = q->Left;
	q->Left = p;
	p = q;
}

void LL1_turn(Vertex*& p) {
	Vertex* q = p->Left;
	if (q->bal == 0) {
		p->bal = -1;
		q->bal = 1;
		Less = false;
	}
	else {
		q->bal = 0;
		p->bal = 0;
	}
	p->Left = q->Right;
	q->Right = p;
	p = q;
}

void BL(Vertex*& p) {
	cout<<"BL-";
	if (p->bal == -1) {
		p->bal = 0;
	}
	else if (p->bal == 0) {
		p->bal = 1;
		Less = false;
	}
	else if (p->bal == 1) {
		if (p->Right->bal >= 0) {
			RR1_turn(p);
			cout<<"RR"<<endl;
		}
		else {
		RL_turn(p);
		cout<<"RL"<<endl;
}
	}
}

void BR(Vertex*& p) {
	cout<<"BR-";
	if (p->bal == 1) {
		p->bal = 0;
	}
	else if (p->bal == 0) {
		p->bal = -1;
		Less = false;

	}
	else if (p->bal == -1) {
		if (p->Left->bal <= 0) {
			LL1_turn(p);
			cout<<"LL"<<endl;
		}
		else {
		LR_turn(p);
		cout<<"LR"<<endl;
	}
	}
}

void del(Vertex*& p, Vertex*& q) {

	if (p->Right != NULL) {
		del(p->Right, q);
		if (Less) {
			BR(p);
		}
	}
	else {	
		q->Data = p->Data;
		q = p;
		p = p->Left;
		Less = true;
	}
}

void DeleteAVL(int Data, Vertex*& p) {
	if (p == NULL) {
		cout << "Vertex doesn't exist";
	}
	else if (p->Data > Data) {
		DeleteAVL(Data, p->Left);
		if (Less) {
			BL(p);
			
		}
	}
	else if (p->Data < Data) {
		DeleteAVL(Data, p->Right);
		if (Less) {
			BR(p);
			
		}
	}
	else {
		Vertex* q = p;
		if (q->Right == NULL) {
			p = q->Left;
			Less = true;
		}
		else if (q->Left == NULL) {
			p = q->Right;
			Less = true;
		}
		else {
			del(q->Left, q);
			if (Less) {
				BL(p);
				
			}
		}
		delete(q);
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
void FreeTree( Vertex* p ) { 
    if (p->Left)   FreeTree(p->Left); 
    if (p->Right)  FreeTree(p->Right); 
    free(p); 
} 

int main() {
	srand(time(NULL));
	int i = 0, temp, j, k;
	Vertex* Root = NULL;
	char letter;
	bool ok=true;
    do {
    	letter=0;
		system("cls");
        cout << "1) Build tree" << endl;
        cout << "2) Delete tree " << endl;
        cout<<"Enter 'q' to exit"<<endl;
		cin >> letter;
        switch (letter) {
            case '1': 
            system("cls");
            cout<<"Enter -1 to exit"<<endl;
                	while(ok) {
		Insp(Root);
		cout<<"\t\t temp=  ";
		cin>>temp;
		if(temp==-1){break;
		}
		cout<<"  ";
		AVL(temp, Root);
		cout<<"tree: ";
		
	}
	cout << endl;
	system("pause");
                break;
            case '2':
        system("cls");
        cout<<"Enter -1 to exit"<<endl;        
		while(Size(Root) != 0) {
        Insp(Root);
		cout<<"\t\t temp=  ";
		cin>>temp;
		if(temp==-1){break;
		}
		cout<<"  ";
		DeleteAVL(temp, Root);
		cout<<"tree: ";
		
	}
	cout << endl;
	system("pause");
			break;
                    }
        if (letter == 'q') {system("cls"); break;}
                } while (true);
	return 0;
}
