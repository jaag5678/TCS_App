typedef struct ll_table {
	int S;
	int V;
	char ***N;
	char *States;
	char Start_N;
	char *Fi; //Set of final states
}ll_table;

class FA {
	ll_table *L;

public:
	FA(int, int);
	void Create();
	void StoreStates(char *, int, int, int &);
	bool Str_Test_N(char *);
	bool State_Exist_N(char);
	bool Recurve(char *, char);
	bool Final(char);
	int get_no(char);

	//For conversion of NFA to DFA
	FA NFA_DFA();
	char * Fetch_States(int, char *);
	void FA_Update(char **, int, int);
	int update_states(char *, char **);
};
