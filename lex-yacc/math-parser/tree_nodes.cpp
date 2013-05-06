#include "tree_nodes.h"

int tree_node::evaluate() {
	
}

int tree_node_num::evaluate() {
	return value;
}

int tree_node_add::evaluate() {
	return left->evaluate() + right->evaluate();
}

int tree_node_brack::evaluate() {
	return expr->evaluate();
}
