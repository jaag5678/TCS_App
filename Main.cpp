#include"Importante.h"
#include"DFA.h"
#include"NFA.h"

int main() {

	int S, V;
	char *STR = NULL;

	cout << "No of states " << endl;
	cin >> S;

	cout << "No of variables" << endl;
	cin >> V;

	NFA a(S, V);

	a.Str_Input_N();

	char c[14] = "0001100011000";

	bool t = a.Str_Test_N(c);
	cout <<t<< endl;

	getchar(); //Optional 
	getchar(); //Optional
	return 0;
}