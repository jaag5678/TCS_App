typedef struct ll_table {
	int S;
	int V;
	vector<int> **N;
	vector<string> States;
	vector<char> Variables;
	string Start_N;
	vector<string> Fi; //Set of final states
	bool epsi = 0; // A tool for epsilon transitions
}ll_table;

class FA {
	ll_table *L;

public:
	FA(int, int, bool);

	//To Create as per user input
	void Create();
	void StoreStates(vector<string> , int, int);
	bool Str_Test_N(string); //To test user's given string in the langugae specified
	bool State_Exist_N(vector<string>, string); 
	bool Recurve(string, string); 
	bool Final(string);
	int get_var(char);
	int get_st(string);

	//For conversion of NFA to DFA
	FA NFA_DFA();
	vector<string> Fetch_States(char, vector<string>);
	void FA_Update(vector<int> **, char, int);
	int update_states(vector<string>, vector<vector<string>> *, int *);
	void update_final(ll_table *, vector<string> , vector<vector<string>>);

	//To print the tabular format of the FA 
	void print();
};