#include <iostream>

/* Parser interface */
#include "parser.i"

using namespace std;

void yyerror(const char* err) {
	cerr << err << endl;
}

int main(int, char**) {
	if(yyparse() == 0) {
		cout << "Balanced parentheses!" << endl;
	} else {
		cout << "Invalid string!" << endl;
	}

	return 0;
}
