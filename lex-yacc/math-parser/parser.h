#ifndef _PARSER_H_
#define _PARSER_H_

#define TOKEN_NUM 257
#define TOKEN_PLUS 258
#define TOKEN_LPAREN 259
#define TOKEN_RPAREN 260
#define YYERRCODE (-1)

#include <iostream>
#include "tree_nodes.h"

typedef union {
	tree_node* node;
	int value;
} YYSTYPE;

/* define the initial stack-sizes */
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#define YYINITSTACKSIZE 500

struct YYSTACKDATA {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
};

class yyFlexLexer;

// Parser class
class math_parser {
	private:
	std::istream *input;
	struct YYSTACKDATA yystack;
	int      yydebug;
	int      yynerrs;

	int      yyerrflag;
	int      yychar;
	int 	 ready;
	YYSTYPE  yyval;
	YYSTYPE  yylval;
	
	yyFlexLexer* lexer;
	tree_node* root;

	protected:
	void yyerror(const char*);
	int yygrowstack();
	void yyfreestack();
	void done_parse();
	public:
	math_parser(std::istream*);
	virtual ~math_parser();

	void ready_parser();
	void ready_parser(std::istream*);

	int parse();
	tree_node* get_parse_tree();	
};

#endif
