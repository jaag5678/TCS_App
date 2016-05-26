//Making a Data Strcuture for A Deterministi Finite Automata
#include<iostream>
#include<string.h>

using namespace std;

typedef struct l_table {
	char **M; //Matrix Representation
	int S;
	int V;
	char *St; //For all states
	char *F; //For final state
	char Start;
}l_table;


class DFA {

	l_table *L;

public:
	DFA(int S, int V);
	void Input();
	bool Str_Inp(char *);
	bool St_Exist(char, int );
};

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

	char g;
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

int main() {

	int S, V;
	char *STR = NULL;

	cout << "No of states " << endl;
	cin >> S;

	cout << "No of variables" << endl;
	cin >> V;

	DFA a(S, V);

	a.Input();

	while (1) {
		char c;
		int off = 0, cnt = 1;
		STR = new char[256];
		cout << "Give a string to test" << endl;

		//Shantanu HEre
		while ((c = getchar()) != (EOF || '\n')) {
			c = STR[off++];
			if (!(off % 256))
				STR = (char *)realloc(STR, sizeof(char) * 256 * (++cnt));
		}
		int t = a.Str_Inp(STR);
		cout << "T" << t << endl;

		cout << "Do you want to test any other string?" << endl;
		cin >> S;

		if (S == 1)
			free(STR);
		else
			break;
	}
	

	getchar();
	getchar();

	return 0;
}

