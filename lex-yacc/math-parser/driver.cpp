#include <iostream>

#include "tree_nodes.h"
#include "parser.h"

using namespace std;

int main(int, char**) {
	math_parser* parser = new math_parser;

	parser->parse();

	cout << parser->get_parse_tree()->evaluate() << endl;

	delete parser;

	return 0;
}
