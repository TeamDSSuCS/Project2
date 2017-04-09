/********************************************************************************/
/* Project: 									*/
/* Author: 									*/
/* Date: 									*/
/* Description:									*/
/********************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    int define(string indent, int current_rule);
    int param_list(string indent, int current_rule);
    int stmt(string indent, int current_rule);
    int literal(string indent, int current_rule);
    int action(string indent, int current_rule);
    int quoted_lit(string indent, int current_rule);
    int any_other_token(string indent, int current_rule);
    int more_tokens(string indent, int current_rule);
    private:
	LexicalAnalyzer * lex;
	ofstream p2file;
	token_type token;
	int program ();
};
	
#endif
