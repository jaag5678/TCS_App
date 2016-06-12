typedef struct ll_table {
	int S;
	int V;
	char ***N;
	char *States;
	char Start_N;
	char *Fi; //Set of final states
}ll_table;

class NFA {
	ll_table *L;

public:
	NFA(int, int);
	void Str_Input_N();
	bool Str_Test_N(char *);
	bool State_Exist_N(char);
	void Store_St(char *, int, int, int &);
	bool Recurve(char *, char);
	bool Final(char);
	int get_no(char);
};
