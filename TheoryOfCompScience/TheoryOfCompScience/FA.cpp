//Creating a Class to define FA's 
#define _CRT_SECURE_NO_WARNINGS

#include"Importante.h"
#include"FA.h"

//Method specifications 

FA::FA(int S, int V) {
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

void FA::Create() {

	//First need to know the first state
	cout << "Enter the first state" << endl;
	cin >> L->Start_N;

	int n = 0;
	int v = 0;
	int k = 0;

	L->States = new char[L->S];
	L->States[k++] = L->Start_N;
	L->States[k] = '\0';

	while (L->S - n) {
		//Start creating a table 
		cout << "For state" << L->States[n] << endl;

		while (L->V - v){
			cout << "For\t" << v;
			char *str = new char[256];

			getchar(); 
			cin.getline(str, 256);
			StoreStates(str, n, v, k);
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
	L->Fi[n] = '\0'; // Since there has to be at least one final state
}

void FA::StoreStates(char *c, int n, int v, int &k) {

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

bool FA::Str_Test_N(char *P) {

	char state = L->States[0];
	if (Recurve(P, state))
		return 1;
}

//Took a lot of time but finally done it. ITs like backtrackking:))
bool FA::Recurve(char *P, char state) {
	int len_1 = strlen(P);
	//int v = 1;
	if (len_1) {
		if (L->N[get_no(state)][*P - '0'] != NULL) {
			int len_2 = strlen(L->N[get_no(state)][*P - '0']);
			while (len_2) 
				if (Recurve((P + 1), L->N[get_no(state)][*P - '0'][--len_2]))
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

bool FA::State_Exist_N(char c) {

	int len = strlen(L->States);
	while (len)
		if (L->States[--len] == c)
			return 1;
	return 0;
}

int FA::get_no(char c) {
	int j = 0;
	while (1) 
		if (L->States[j++] == c)
			return j-1;
}

bool FA::Final(char c) {
	int j = strlen(L->Fi);
	while (j) 
		if (L->Fi[--j] == c)
			return 1;
	return 0;
}


//Functions to Convert to DFA
void FA::FA_Update(char **L, int V, int off) {
	L[V] = new char[1];
	L[V][0] = 'A' + off;
}

int FA::update_states(char *str, char **states) {
	int t = 0;
	while (states[t]) {
		if (strcmp(states[t], str)) 
			t++;
		else 
			return t;
	}
	//if it comes here means it has no match
	states = (char **)realloc(states, sizeof(char *)* (t + 1));
	states[t] = (char *)malloc(strlen(str));
	strcpy(states[t], str);
	return t;
}

char * FA::Fetch_States(int V, char *State) {
	int l = strlen(State);
	int tot = 0;

	while (l--) 
		tot += strlen(L->N[get_no(State[l])][V]);

	char *str = new char[tot];
	while (strlen(State) - ++l) 
		strcat(str, L->N[get_no(State[l])][V]);
	return str;
}

FA FA::NFA_DFA() {
	char **states = NULL;
	FA A(1, L->V);
	states = (char **)malloc(sizeof(char*));
	states[0] = (char *)malloc(sizeof(char));
	states[0][0] = L->Start_N; //Keep the start state in list

	A.L->Start_N = L->Start_N;
	A.L->States = new char[1];

	A.L->States[0] = L->States[0];
	
	int V = L->V;
	int off = 0;
	while (states[off]) {
		while (V) {
			//char *str = Fetch_States(L->V - V, states[off]);
			//FA_Update will update the automata and update_string will return an offset and update states 
			FA_Update(A.L->N[off], L->V - V, update_states(Fetch_States(L->V - V, states[off]), states));
			V--;
		}
		off++;
	}
	A.L->States = new char[off];
	while (off--) 
		A.L->States[off] = 'A' + off;

}