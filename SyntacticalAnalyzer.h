/********************************************************************************/
/* Project: Project 2                                   */
/* Author:      David Tauraso, Lucas Winkelmann, Matthew Bennett                            */
/* Date:    4/13/17                             */
/* Description:     This analyzes the syntax of a subset of Guile Scheme                            */
/********************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    int define(int current_rule);
    int param_list(int current_rule);
    int else_part(int current_rule);
    int stmt(int current_rule);
    int stmt_list(int current_rule);
    int literal(int current_rule);
    int action(int current_rule);
    int quoted_lit(int current_rule);
    int any_other_token(int current_rule);
    int more_tokens(int current_rule);
    int more_defines(int current_rule);
    private:
	LexicalAnalyzer * lex;
	ofstream p2file;
	token_type token;
	int program ();
};
	
#endif
