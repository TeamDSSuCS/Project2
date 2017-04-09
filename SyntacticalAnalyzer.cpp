/********************************************************************************/
/* Project: 									*/
/* Author: 									*/
/* Date: 									*/
/* Description:									*/
/********************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "SyntacticalAnalyzer.h"
#include <map> 

using namespace std;

int ll1table[][32] = 
{
{-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,2,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{4,3,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,5,-1,5,6,6,5,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,9,-1,8,-2,-2,7,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-2,-1,-2,-2,-2,10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,12,12,12,-2,-2,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
{-1,13,13,13,14,14,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13},
{-1,-1,-1,15,-2,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,17,-1,17,-2,18,17,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,41,-2,-1,-1,-1,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,42,43},
{-1,44,55,45,-2,-2,46,72,48,51,47,52,53,54,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,49,50}};

static std::map<std::string, int> token_to_col = {
					{"EOF_T",0},
					{"LPAREN_T",1},
					{"DEFINE_T",2},
					{"IDENT_T",3},
					{"RPAREN_T",4},
					{"{}",5},
					{"NUMLIT_T",6},
					{"QUOTE_T",7},
					{"IF_T",8},
					{"LISTOP_T",9},
					{"CONS_T",10},
					{"AND_T",11},
					{"OR_T",12},
					{"NOT_T",13},
					{"NUMBERP_T",14},
					{"SYMBOLP_T",15},
					{"LISTP_T",16},
					{"ZEROP_T",17},
					{"NULLP_T",18},
					{"CHARP_T",19},
					{"STRINGP_T",20},
					{"PLUS_T",21},
					{"MINUS_T",22},
					{"DIV_T",23},
					{"MULT_T",24},
					{"EQUALTO_T",25},
					{"GT_T",26},
					{"LT_T",27},
					{"GTE_T",28},
					{"LTE_T",29},
					{"DISPLAY_T",30},
					{"NEWLINE_T",31}};



SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename) {
/********************************************************************************/
/* This function will								*/
/********************************************************************************/
	lex = new LexicalAnalyzer (filename);
	int fnlength = strlen (filename);
	filename[fnlength-2] = 'p';
	filename[fnlength-1] = '2';
	p2file.open (filename);
	//token = lex->GetToken();
	int errors = program ();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
/********************************************************************************/
/* This function will								*/
/********************************************************************************/
    p2file.close();
	delete lex;
}

int SyntacticalAnalyzer::action(int current_rule) {
    int errors = 0;
    token = lex->GetToken();
    p2file << "Starting <action>. Current token = " << lex->GetTokenName(token) << endl;
    if (lex->GetTokenName(token) == "DISPLAY_T") {
        p2file << "Using rule 42" << endl;
        token = lex->GetToken();
        errors += stmt(4);
    } else if (lex->GetTokenName(token) == "LISTOP_T") {
        p2file << "Using rule 20" << endl;
        token = lex->GetToken();
        errors += stmt(4);
    } else if (lex->GetTokenName(token) == "NEWLINE_T") {
        p2file << "Using rule 43" << endl;
        token = lex->GetToken();
    }
    p2file << "Ending <action>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    token = lex->GetToken();
    return 0;
}

int SyntacticalAnalyzer::else_part(int current_rule) {
    int errors = 0;
    return errors;
}


int SyntacticalAnalyzer::stmt_list(int current_rule) {
    int errors = 0;
    p2file << "Starting <stmt_list>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case 5: {
            errors += stmt(4);
            errors += stmt_list(3);
            break;
        }
        case 6: {
            break;
        }
    }
    p2file << "Ending <stmt_list>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::param_list(int current_rule) {
    int errors = 0;
    p2file << "Starting <param_list>. Current token = " << lex->GetTokenName(token) << endl;
    if (lex->GetTokenName(token) == "RPAREN_T") {
        p2file << "Using rule 16" << endl;
    } else {
        token = lex->GetToken();
        errors += param_list(8);
    }
    p2file << "Ending <param_list>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return 0;
}

int SyntacticalAnalyzer::define(int current_rule) {
    int errors = 0;
    p2file << "Starting <define>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "DEFINE_T")
        p2file << "Error" << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "LPAREN_T")
        p2file << "Error" << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "IDENT_T")
        p2file << "Error" << endl;
    token = lex->GetToken();
    errors += param_list(8);
    token = lex->GetToken();
    errors += stmt(4);
    errors += stmt_list(3);
    token = lex->GetToken();
    p2file << "Ending <define>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return 0;
}

int SyntacticalAnalyzer::more_tokens(int current_rule) {
    int errors = 0;
    p2file << "Starting <more_tokens>. Current token = " << lex->GetTokenName(token) << " Lex: " << lex->GetLexeme()<< endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(13): { 
            errors += any_other_token(11);
            errors += more_tokens(7);
            }
        case(14): {

        }
    }
    p2file << "Ending <more_tokens>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::any_other_token(int current_rule) {
    int errors = 0;
    p2file << "Starting <any_other_token>. Current token = " << lex->GetTokenName(token) << " Lex: " << lex->GetLexeme()<< endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(44): {
            token = lex->GetToken();
            errors += more_tokens(7);
            break;
            //token = lex->GetToken();
        }
        default: break;
        //default: token = lex->GetToken();
    }
    token = lex->GetToken();
    p2file << "Ending <any_other_token>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::quoted_lit(int current_rule) {
    int errors = 0;
    token = lex->GetToken();
    p2file << "Starting <quoted_lit>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(12): 
            errors += any_other_token(11);
    }
    p2file << "Ending <qutoed_lit>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::literal(int current_rule) {
    int errors = 0;
    p2file << "Starting <literal>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(11): 
            errors += quoted_lit(6);
            break;
    }
    p2file << "Ending <literal>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
}

int SyntacticalAnalyzer::more_defines(int current_rule) {
    int errors = 0;
    p2file << "Starting <more_defines>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    p2file << "Ending <more_defines>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::stmt(int current_rule) {
    int errors = 0;
    //token = lex->GetToken();
    p2file << "Starting <stmt>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case 9:
            errors += action(next_rule);
            break;
        case 7:
            errors += literal(5);
            break;
    }
    p2file << "Ending <stmt>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::program ()
{
/********************************************************************************/
/* This function will								*/
/********************************************************************************/
    //p2file<< "Program function called" << endl;
	lex->debug << "program function called\n";
	p2file<< "program\n";
	int errors = 0;
	// dfa evaluator
	// token should be in the firsts of program
	// if true... keep going
	// if false...
	// Error message -
	// 	then keep going or keep getting token until token is
	// 	in the firsts of program

	// errors += define ();

	// errors += more_defines ();

    p2file << "Starting <program>. ";
    int current_rule = 0;
    token = lex->GetToken();
    p2file << "Current Token is: " << lex->GetTokenName(token)<< endl; 
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    p2file << "Using rule " << next_rule << std::endl;
    switch(next_rule) {
        case 1: {
            errors += define(next_rule);
            errors += more_defines(2);
            p2file << "Ending <program>. Current Token = " << lex->GetTokenName(token) << ". Errors = "<< errors << endl;
            break;
            //stmt(4);
        }
    }
    //errors += define(next_rule);
	if (token != EOF_T)
	{
		lex->ReportError ("Expected end of file; " + lex->GetLexeme ());
		errors++;
	}

	// token should be in the follows of program
	// if true... keep going
	// if false...
	// Error message -
	// 	then keep going or keep getting token until token is
	// 	in the follows of program

    //std::p2File<< "Program function called" << endl;
	lex->debug << "program function returning " << errors << " errors\n";
	return errors;
}

