//Making a Data Strcuture for A Deterministi Finite Automata
#include"Importante.h"
#include"DFA.h"

using namespace std;


DFA::DFA(int S, int V) {
	L = new l_table;
	L->S = S;
	L->V = V;
	L->M = new char*[S];
	L->St = new char[S];

	while (S)
		L->M[--S] = new char[V];
}

void DFA::Input() {
	cout << "Enter the transtions for each state starting from start state" << endl;

	//char g;
	int x, y;
	int i, j, k, cnt;

	i = 0;
	j = 0;
	k = 0;
	x = L->V;
	y = 0;
	cnt = 0;

	cout << "Start state " << endl;
	cin >> L->Start;

	L->St[k++] = L->Start;
	cout << "Del";

	while (y < x)
		cout << " "<< y++ << " ";
	cout << endl;

	x = L->S;
	y = L->V;

	while (cnt < k) {
		cout << L->St[cnt++];
		while (y > 0) {

			cin >> L->M[i][j++];
			if (!(St_Exist(L->M[i][j - 1], k)))
				L->St[k++] = L->M[i][j-1];
			y--;
		}
		y = L->V;
		j = 0;
		i++;
	}

	cout << "How many final states exist ?" << endl;
	cin >> x;

	y = 0;
	L->F = new char[x];

	cout << "Write the final states" << endl;

	while (x) {
		cin >> L->F[y++];
		x--;
	}
}

bool DFA::Str_Inp(char *P) {

	int len;
	int c, i, j;
	char state;

	//cout << "Zzz";
	state = L->Start;
	i = 0;
	j = 0;
	len = strlen(P);

	//cout << " zzz";
	while (len) {
		c = P[i++] - '0';
		state = L->M[j][c];

		j = 0;
		while (1) {
			if (state == L->St[j])
				break;
			j++;
		}
		len--;
	}

	len = strlen(L->F);
	c = 0;
	i = 0;

	while (len) {
		if (state == L->F[i++])
			c = 1;
		len--;
	}
	return c;
}

bool DFA::St_Exist(char c, int k) {
	int l = 0;
	do {
		if (L->St[l++] == c)
			return true;
	} while (l < k);
	return false;
}
