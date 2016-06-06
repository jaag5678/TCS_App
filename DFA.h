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
	bool St_Exist(char, int);
};
