//Creating a Class to define NFA's 
#define _CRT_SECURE_NO_WARNINGS

#include"Importante.h"
#include"NFA.h"

//Method specifications 

NFA::NFA(int S, int V) {
	L = new ll_table;
	L->S = S;
	L->V = V;
	L->N = new char **[S];
	
	int v = V;
	while (S) {
		L->N[--S] = new char *[V];
		while (v)
			L->N[S][--v] = NULL;
		v = V;
	}
	L->Fi = NULL;
	L->States = NULL;
}

void NFA::Str_Input_N() {

	//First need to know the first state
	cout << "Enter the first state" << endl;
	cin >> L->Start_N;

	int n;
	int v;
	int k;

	L->States = new char[L->S];
	n = 0;
	v = 0;
	k = 1;

	L->States[n] = L->Start_N;
	L->States[n + 1] = '\0';

	while (L->S - n) {
		//Start creating a table 
		cout << "For state" << L->States[n] << endl;

		while (L->V - v){
			cout << "For\t" << v;
			char *str = new char[256];

			getchar(); // Optional 
			cin.getline(str, 256);
			Store_St(str, n, v, k);
			v++;
		}
		v = 0;
		n++;
	}

	char *f = new char[256];
	cout << "Enter the no of final States" << endl;
	getchar();
	cin.getline(f, 256);

	int len = strlen(f);
	n = 0;

	while (len) {
		if (isalpha(f[len-1])) {
			L->Fi = (char *)realloc(L->Fi, sizeof(char)*(++n + 1));
			L->Fi[n - 1] = f[--len];
		}
	}
	L->Fi[n] = '\0';
}

void NFA::Store_St(char *c, int n, int v, int &k) {

	int t = 0;
	int f = 0;
	int l = strlen(c);

	//Need to end the loop
	while (l--){
		if (!(isalpha(c[t++])))
			continue;
		L->N[n][v] = (char*)realloc(L->N[n][v], sizeof(char) * (f + 2));
		L->N[n][v][f++] = c[t - 1];
		L->N[n][v][f] = '\0';
		if (!State_Exist_N(c[t - 1])) {
			L->States[k++] = c[t - 1];
			L->States[k] = '\0';
		}
	}
	if (!f)
		L->N[n][v] = NULL;
}

bool NFA::State_Exist_N(char c) {

	int len = strlen(L->States);
	while (len)
		if (L->States[--len] == c)
			return 1;
	return 0;
}

bool NFA::Str_Test_N(char *P) {

	char state = L->States[0];
	if (Recurve(P, state))
		return 1;
}

//Took a lot of time but finally done it. ITs like backtrackking:))
bool NFA::Recurve(char *P, char state) {
	int len_1 = strlen(P);
	int v = 0;
	if (len_1) {
		if (L->N[get_no(state)][*P - '0'] != NULL) {
			int len_2 = strlen(L->N[get_no(state)][*(P + v) - '0']);
			while (len_2) 
				//state = L->N[get_no(state)][*P - '0'][--len_2];
				if (Recurve((P + ++v), L->N[get_no(state)][*P - '0'][--len_2]))
					return 1;
				return 0; //Imp to Understand
		}
		else
			return 0;
	}
	if (Final(state))
		return 1;
	return 0;
}

int NFA::get_no(char c) {
	int j = 0;
	while (1) 
		if (L->States[j++] == c)
			return j-1;
}

bool NFA::Final(char c) {
	int j = strlen(L->Fi);
	while (j) 
		if (L->Fi[--j] == c)
			return 1;
	return 0;
}