//Creating a Class to define FA's 
#define _CRT_SECURE_NO_WARNINGS

#include"Importante.h"
#include"FA.h"

//Method specifications 

FA::FA(int S, int V, bool epsi) {
	L = new ll_table;
	L->S = S;
	L->V = V;
	L->epsi = epsi;
	L->N = new vector<int> *[S];
	while (S) {
		if (!epsi)
			L->N[--S] = new vector<int>[V];
		else
			L->N[--S] = new vector<int>[V + 1];
	}
}

void FA::Create() {

	//First need to know the first state
	cout << "Enter the first state" << endl;
	cin >> L->Start_N;

	cout << "Enter all the variables" << endl;
	char c;
	cin.ignore();
	do {
		cin >> c;
		L->Variables.push_back(c);
	} while (getchar() != '\n');

	int n = 0;
	int v = 0;
	int k = 0;

	L->States.push_back(L->Start_N);

	cout << "Start filling the state table as asked.. If a given transition goes to multiple states Seperate them with spaces and write them" << endl;
	while (L->S - n) {
		//Start creating a table
		bool t = L->epsi;
		cout << "For state " << L->States[n] << endl;
		while (L->V - v){

			if (t) 
				cout << "For epsilon ";
			else
				cout << "For " << L->Variables[v]<<" ";
			vector<string> T;
			string temp;
			do {
				cin >> temp;
				T.push_back(temp);
			} while (getchar() != '\n');
			if (t) {
				t = 0;
				StoreStates(T, n, L->V);
			}
			else {
				StoreStates(T, n, v);
				v++;
			}
		}
		v = 0;
		n++;
	}

	char *f = new char[256];
	cout << "Enter the no of final States." << endl;
	cout << "If more than one final state exist seperate them with spaces and mention them all in one line" << endl;
	
	string temp;
	do {
		//cin.getline(f, 256);
		cin >> temp;
		L->Fi.push_back(temp);
	} while (getchar() != '\n');
}

void FA::StoreStates(vector<string> T, int n, int v) {

	int t = 0;
	int f = 0;
	int l = T.size();

	if (T[0] == "-")
		return;

	while (l--) {
		if (!State_Exist_N(L->States, T[l]))
			L->States.push_back(T[l]);
		L->N[n][v].push_back(get_st(T[l]));
	}
}

bool FA::Str_Test_N(string P) {

	string state;
	if (L->epsi) {
		FA A = NFA_DFA();
		state = A.L->States[0];
		if (A.Recurve(P, state))
			return 1;
	}
	else {
		state = L->States[0];
		if (Recurve(P, state))
			return 1;
	}
	return 0;
}

//Took a lot of time but finally done it. ITs like backtrackking:))
bool FA::Recurve(string P, string state) {
	int len_1 = P.size();
	//int v = 1;
	if (len_1) {
		if (L->N[get_st(state)][get_var(P[0])].size() != 0) {
			int len_2 = L->N[get_st(state)][get_var(P[0])].size();
			char t = P[0];
			P.erase(P.begin());
			while (len_2)
				if (Recurve(P, L->States[L->N[get_st(state)][get_var(t)][--len_2]]))
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

bool FA::State_Exist_N(vector<string> States, string c) {

	int len = States.size();
	while (len--)
		if (States[len] == c)
			return 1;
	return 0;
}
int FA::get_var(char c) {
	int j = L->Variables.size();
	while (j--)
		if (L->Variables[j] == c)
			return j;
	//Return Eroor here
}
int FA::get_st(string c) {
	int j = 0;
	while (1)
		if (L->States[j++] == c)
			return j - 1;
}
bool FA::Final(string c) {
	int j = L->Fi.size();
	while (j--)
		if (L->Fi[j] == c)
			return 1;
	return 0;
}


//Functions to Convert to DFA
void FA::FA_Update(vector<int> **Z, char V, int of) {
	Z[0][get_var(V)].push_back(of);
}

int FA::update_states(vector<string> S, vector<vector<string>> *States, int *k) {
	int t = L->States.size();
	bool tog = 0;

	//First need to remove the repetitive occuring of states in the vector received
	//First tym use of iterators
	while (t--){
		string c = L->States[t];
		int l = S.size();
		while (l--) {
			if (S[l] == c && !tog)
				tog = 1;
			else if(S[l] == c){
				vector<string> ::iterator p;
				p = S.begin();
				p += l;
				S.erase(p);
			}
		}
		tog = 0;
	}
	t = States[0].size();
	while (t--) {
		if (States[0][t] == S)
			return t;
	}
	//if it comes here means it has no match
	*k = *k + 1;
	States[0].push_back(S);
	return *k;
}

vector<string> FA::Fetch_States(char V, vector<string> State) {
	int l = 0;
	int tot = 0;

	if (L->epsi) {
		while (l < State.size()){
			int m = L->N[get_st(State[l])][L->V].size(); //Epsilon's data
			while (m--) {
				string s = L->States[L->N[get_st(State[l])][L->V][m]];
				if (!State_Exist_N(State, s ))
					State.push_back(s);
			}
			l++;
		}
	}

	l = State.size();
	vector<string> Str;
	while (l--) {
		int m = L->N[get_st(State[l])][get_var(V)].size();
		while (m--) 
			Str.push_back(L->States[L->N[get_st(State[l])][get_var(V)][m]]);
	}
	return Str;
}

void FA::update_final(ll_table *Z, vector<string> F_NFA,  vector<vector<string>> states) {

	int t = states.size();
	
	while (t--) {
		int l = states[t].size();
		while (l--) {
			int m = F_NFA.size();
			while (m--) {
				if (F_NFA[m] == states[t][l]) {
					Z->Fi.push_back(Z->States[t]);
					break;
				}
			}
		}
	}
}

FA FA::NFA_DFA() {
	vector<vector<string>> States;
	FA A(1, L->V, 0);

	vector<string> t;
	t.push_back(L->States[0]);
	States.push_back(t); // The Start State

	A.L->Start_N = L->Start_N;
	A.L->V = L->V;

	int V = L->V;
	int off = 0;
	int k = 0;
	while (off <= k) {
		A.L->N = (vector<int> **)realloc(A.L->N, sizeof(vector<int> *) * (k + 1));
		A.L->N[off] = new vector<int> [L->V];
		while (V) {
			FA_Update(&A.L->N[off], L->Variables[L->V - V],  update_states(Fetch_States(L->Variables[L->V - V], States[off]), &States, &k));
			V--;
		}
		off++;
		V = L->V;
	}
	cout << off << endl;
	A.L->S = k + 1;
	off = L->S;
	int t1 = off - k;
	/*while (off--)
		A.L->States.push_back(L->States[off]);*/
	cout << "We need to define new states for the DFA sinze the existing names have been used up." << endl;
	cout << "Plz enter the names for each state on a new line" << endl;
	while (k + 1) {
		
		cout << "States remaining " << k + 1;
		string temp;
		cin >> temp;
		A.L->States.push_back(temp);
		k--;
	}
	cout << "Thank you for your assistance" << endl;

	//update the variables too
	off = 0;
	while (off < L->V) 
		A.L->Variables.push_back(L->Variables[off++]);
	update_final(A.L, L->Fi, States);

	return A;
}

//WOnt be much useful just for testting the correctness of the above algorithm
void FA::print() {

	cout << "D ";
	for (int i = 0; i < L->V; i++)
		cout << L->Variables[i] << " ";
	cout << endl;
	//Print the FIrst state then along with the var print the transition states
	for (int i = 0; i < L->S; i++) {
		cout << L->States[i] << "  ";
		for (int j = 0; j < L->V; j++) {
			cout << L->States[L->N[i][j][0]] << " ";
		}
		cout << endl;
	}
}