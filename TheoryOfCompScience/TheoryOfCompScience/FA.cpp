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
		if (isalpha(f[len - 1])) {
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
	//IF no state transition
 	if (!f) {
		L->N[n][v] = (char*)malloc(sizeof(char));
		L->N[n][v] = "";
		cout << L->N[n][v] << endl;
	}
}

bool FA::Str_Test_N(char *P) {

	char state = L->States[0];
	if (Recurve(P, state))
		return 1;
	return 0;
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
			return j - 1;
}

bool FA::Final(char c) {
	int j = strlen(L->Fi);
	while (j)
		if (L->Fi[--j] == c)
			return 1;
	return 0;
}


//Functions to Convert to DFA
void FA::FA_Update(char ***Z, int V, int of) {

	Z[0][V] = new char[1];
	Z[0][V][0] = 'A' + of;
	Z[0][V][1] = '\0';

}

int FA::update_states(char *str, char ***states, int *k) {
	int t = 0;
	while (states[0][t] != '\0') {
		if (strcmp(states[0][t], str))
			t++;
		else
			return t;
	}
	//if it comes here means it has no match
	*k = *k + 1;
	states[0] = (char **)realloc(states[0], sizeof(char *)* (t + 1) + 1);
	states[0][t] = (char *)malloc(strlen(str));
	strcpy(states[0][t], str);
	states[0][t + 1] = '\0';
	return t;
}

char * FA::Fetch_States(int V, char *State) {
	int l = strlen(State);
	int tot = 0;

	//Error here since we did not allocate '\0' for empty strings properly
	cout << L->N[1][0] << endl;
	while (l--)
		tot += strlen(L->N[get_no(State[l])][V]);

	char *str = new char[tot + 1];
	//str[tot] = '\0';
	while (strlen(State) - ++l) {
		//str[l] = L->N[get_no(State[l])][V];
		if (!l)
			strcpy(str, L->N[get_no(State[l])][V]);
		else
			strcat(str, L->N[get_no(State[l])][V]);
		cout << str << endl;;
	}
	str[tot] = '\0';
	return str;
}

void FA::update_final(ll_table *Z, char *F_NFA,  char **states) {

	int t = 0;
	int cnt = 0;
	bool *A = new bool[Z->S] {0};
	while (states[t]) {
		int s = strlen(states[t]);
		while (s--) {
			int r = strlen(F_NFA);
			while (r--) {
				if (F_NFA[r] == states[t][s]) {
					A[t] = 1;
					cnt++;
					break;
				}
			}
			if (A[t])
				break;
		}
		t++;
	}

	Z->Fi = new char[cnt];
	cnt = 0;
	for (int i = 0; i < Z->S; i++)
		if (A[i])
			Z->Fi[cnt++] = 'A' + i;
}

FA FA::NFA_DFA() {
	char **states = NULL;
	FA A(1, L->V);
	states = (char **)malloc(sizeof(char*) + 1);
	states[0] = (char *)malloc(sizeof(char) + 1);
	states[0][0] = L->Start_N; //Keep the start state in list
	states[0][1] = '\0';
	states[1] = '\0';

	A.L->Start_N = L->Start_N;
	A.L->States = new char[1];

	A.L->States[0] = L->States[0];

	int V = L->V;
	int off = 0;
	int k = 0;
	while (off <= k) {
		A.L->N = (char ***)realloc(A.L->N, sizeof(char **) * (k + 1));
		A.L->N[k] = (char **)malloc(sizeof(char *));
		while (V) {
			//char *str = Fetch_States(L->V - V, states[off]);
			//FA_Update will update the automata and update_string will return an offset and update states 
			FA_Update(&A.L->N[off], L->V - V, update_states(Fetch_States(L->V - V, states[off]), &states, &k));
			cout << "K" << k << endl;
			V--;
		}
		off++;
		V = L->V;
	}
	cout << off << endl;
	A.L->S = off;
	A.L->States = new char[off];
	while (off--)
		A.L->States[off] = 'A' + off;
	cout << A.L->States<<endl;
	update_final(A.L, L->Fi, states);

	return A;
}

//WOnt be much useful just for testting the correctness of the above algorithm
void FA::print() {

	cout << "Del ";
	for (int i = 0; i < L->V; i++)
		cout << i << " ";
	cout << endl;
	//Print the FIrst state then along with the var print the transition states
	for (int i = 0; i < L->S; i++) {
		cout << L->States[i] << "  ";
		for (int j = 0; j < L->V; j++) {
			cout << L->N[i][j][0] << " ";
		}
		cout << endl;
	}
}