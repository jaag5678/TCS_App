#include"Importante.h"
//#include"DFA.h"
#include"FA.h"

int main() {

	int S, V;
	char *STR = NULL;

	cout << "No of states " << endl;
	cin >> S;

	cout << "No of variables" << endl;
	cin >> V;

	FA a(S, V);

	a.Create();

	char c[21] = "00011000110001111111";

	bool t = a.Str_Test_N(c);
	cout <<t<< endl;

	getchar(); //Optional 
	getchar(); //Optional
	return 0;
}