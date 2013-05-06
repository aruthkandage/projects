#include <iostream>

/* Parser interface */
#include "parser.i"
#include "tree_nodes.h"

using namespace std;

void yyerror(const char* err) {
	cerr << err << endl;
}

int main(int, char**) {
	cout << yyparse() << endl;
	return 0;
}
