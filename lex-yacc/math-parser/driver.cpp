#include <iostream>
#include <string>
#include <sstream>

#include "tree_nodes.h"
#include "parser.h"

#define NULL_TERMIN ('\0')
#define INPUT_SIZE (256)

using namespace std;

int main(int, char**) {
	math_parser* parser = new math_parser(&cin);
	char input[INPUT_SIZE];

	while(!cin.eof()) {
		cout << "> ";
		cin.getline(input, INPUT_SIZE);
		if(input[0] == NULL_TERMIN) {
			cout << endl << "See ya!" << endl;
			break;
		}

		istringstream inp_stream(input);
		parser->ready_parser(&inp_stream);
		if(parser->parse()) {
			cout << "Bad input!" << endl;
		} else {
			int result = parser->get_parse_tree()->evaluate();
		
			cout << result << endl;
		}
	}
	
	delete parser;

	return 0;
}
