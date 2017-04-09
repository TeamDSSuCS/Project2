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
{{-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,2,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-2,3,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,5,-1,5,-2,6,5,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,9,-1,8,-2,-2,7,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1},
{-1,-2,-1,-2,-2,-2,10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{ -1, 12, 12, 12, -2, -2, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},
{ -1, 13, 13, 13, -2, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
{ -1, -1, -1, 15, -2, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{ -1, 17, -1, 17, -2, 18, 17, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{ -1, -1, -1, 41, -2, -1, -1, -1, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43},
{ -1, 44, 55, 45, -2, -2, 46, 72, 48, 51, 47, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 49, 50}};

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



SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
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

int SyntacticalAnalyzer::action(string indent, int current_rule) {
    int errors = 0;
    token = lex->GetToken();
    cout << indent << "Starting <action>. Current token = " << lex->GetTokenName(token) << endl;
    if (lex->GetTokenName(token) == "DISPLAY_T") {
        cout << indent << "Using rule 42" << endl;
        stmt(indent + "    ", 4);
    } else if (lex->GetTokenName(token) == "LISTOP_T") {
        cout << indent << "Using rule 20" << endl;
        stmt(indent + "    ", 4);
    }
    return 0;
}

int SyntacticalAnalyzer::param_list(string indent, int current_rule) {
    int errors = 0;
    cout << indent << "Starting <param_list>. Current token = " << lex->GetTokenName(token) << endl;
    if (lex->GetTokenName(token) == "RPAREN_T") {
        cout << indent << "Using rule 16" << endl;
    } else {
        token = lex->GetToken();
    }
    cout << indent << "Ending <param_list>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return 0;
}

int SyntacticalAnalyzer::define(string indent, int current_rule) {
    int errors = 0;
    cout << indent << "Starting <define>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    cout << indent << "Using rule " << next_rule << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "DEFINE_T")
        cout << indent << "Error" << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "LPAREN_T")
        cout << indent << "Error" << endl;
    token = lex->GetToken();
    if (lex->GetTokenName(token) != "IDENT_T")
        cout << indent << "Error" << endl;
    token = lex->GetToken();
    param_list(indent + "    ", next_rule);
    cout << indent << "Ending <define>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return 0;
}

int SyntacticalAnalyzer::more_tokens(string indent, int current_rule) {
    int errors = 0;
    // if current is lparame
    if(lex->GetTokenName(token) == "LPAREN_T" && current_rule == 7)
    {
    	cout << indent << "need to go to more tokens\n";
    }
	//if(lex->GetTokenName(token) != "IDENT_T")
	//{
		//cout << indent << "got again\n";
	    //token = lex->GetToken();
	    //}
    // at rparen_t
    if(lex->GetTokenName(token) == "RPAREN_T")
    {	// more_tokens is on lambda
	    cout << indent << "Starting <more_tokens>. Current token = " << lex->GetTokenName(token) << endl;

	    cout << indent << "Using rule 14" << endl;
	    cout << indent << "Ending <more_tokens>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;

    	return errors;
    }
    cout << indent << "Starting <more_tokens>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule;
    //if(lex->GetTokenName(token) != "RPAREN_T")

     next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
	//else{
		// should be at rule 14
	  // 	cout << indent << current_rule << " " <<"RPAREN_T\n";
		//return errors;
//}
    	//return errors;
    // more_tokens at RPAREN_T == leave function
    //if(next_rule >= 0)
    cout << indent << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(13): { 
        	cout << endl;
            any_other_token(indent + "    ", 11);
            cout << endl;

            cout << indent << lex->GetTokenName(token) << endl;
            // will eventually result in lambda
            more_tokens(indent + "    ", 7);
            }

    }
    cout << indent << "Ending <more_tokens>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::any_other_token(string indent, int current_rule) {
    int errors = 0;
    cout << indent << "Starting <any_other_token>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    cout << indent << "Using ruler " << next_rule << endl;
    switch(next_rule) {
        case(44): 
        {
        	cout << endl;
        	token = lex->GetToken();
        	more_tokens(indent + "    ", 7);
        }
        case(51):
        {
        	cout << indent << "got here\n";
        		            token = lex->GetToken();
    cout << indent << " Current token = " << lex->GetTokenName(token) << endl;
    cout << next_rule << endl;
    			break;
        }
        case(45): {
        	// need to get the next token name so the next function has it
        //	token = lex->GetToken();
        //	cout << "here\n";
            //if(lex->GetTokenName(token) == "IDENT_T")
            //{
	            token = lex->GetToken();
	        	cout << indent << "here\n";

	        //}

        }
    }
    cout << indent << "Ending <any_other_token>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::quoted_lit(string indent, int current_rule) {
    int errors = 0;
    token = lex->GetToken();
    cout << indent<< "Starting <quoted_lit>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    cout << indent << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(12):{
        	cout << endl;
        	any_other_token(indent + "    ", 11);}
    }
    cout << indent << "Ending <qutoed_lit>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return errors;
}

int SyntacticalAnalyzer::literal(string indent, int current_rule) {
    int errors = 0;
    cout << indent << "Starting <literal>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    cout << indent << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(11): quoted_lit(indent + "    ", 6);
    }
    cout << indent << "Ending <literal>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
}

int SyntacticalAnalyzer::stmt(string indent, int current_rule) {
    int errors = 0;
    token = lex->GetToken();
    cout << indent << "Starting <stmt>. Current token = " << lex->GetTokenName(token) << endl;
    int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
    cout << indent << "Using rule " << next_rule << endl;
    switch(next_rule) {
        case(9): action(indent + "    ", next_rule);
        case(7): literal(indent + "    ", 5);
    }
    cout << indent << "Ending <stmt>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
    return 0;
}

int SyntacticalAnalyzer::program ()
{
/********************************************************************************/
/* This function will								*/
/********************************************************************************/
cout<< "Program function called" << endl;
	lex->debug << "program function called\n";
	p2file << "program\n";
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

    std::cout << "Starting <program>" << std::endl;
    int current_rule = 0;
    while (token != EOF_T) {
        token = lex->GetToken();
        cout << "Current Token is: " << lex->GetTokenName(token)<< endl; 
        int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
        cout << "Using rule " << next_rule << std::endl;
        switch(next_rule) {
            case 1: {
                define("", next_rule);
                stmt("", 4);
            }
        }
        errors += define("", next_rule);
    }
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

cout<< "Program function called" << endl;
	lex->debug << "program function returning " << errors << " errors\n";
	return errors;
}
