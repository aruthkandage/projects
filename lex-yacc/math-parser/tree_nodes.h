#ifndef TREE_NODES_H
#define TREE_NODES_H

#include <cstddef>

/* Base class of a tree node */
class tree_node {
	public:
	tree_node() {}
	virtual ~tree_node() {}

	virtual int evaluate();
};

/* Number */
class tree_node_num : public tree_node {
	private:
	int value;
	public:
	tree_node_num() : value(0) {}
	tree_node_num(int n) : value(n) {}
	~tree_node_num() {}

	int evaluate();
};

/* Add */
class tree_node_add : public tree_node {
	private:
	tree_node* left;
	tree_node* right;
	public:
	tree_node_add() : left(NULL), right(NULL) {}
	tree_node_add(tree_node* l, tree_node* r) : left(l), right(r) {}
	virtual ~tree_node_add() {
		if(left) delete left;
		else if(right) delete right;
	}

	int evaluate();
};

/* Expression in brackets */
class tree_node_brack : public tree_node {
	private:
	tree_node* expr;
	public:
	tree_node_brack() : expr(NULL) {}
	tree_node_brack(tree_node* e) : expr(e) {}
	~tree_node_brack() {
		if(expr) delete expr;
	}

	int evaluate();
};

#endif
