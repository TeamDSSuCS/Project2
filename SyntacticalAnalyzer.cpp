/********************************************************************************/
/* Project: 									*/
/* Author: 									*/
/* Date: 									*/
/* Description:									*/
/********************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

int ll1table[][16] = 
{{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-2,5 ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-2,7 ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-2,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,12,-2,12,12,12,12,12,12,12,12,12,12,12,12,12},
 {-1,13,-2,13,13,13,13,13,13,13,13,13,13,13,13,13},
 {-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-2,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
 {-1,-1,-2,-1,19,21,23,25,27,29,31,33,35,37,39,42},
 {-1,55,-2,46,48,47,53,56,58,60,62,64,66,68,70,49}};


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
	token = lex->GetToken();
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

int SyntacticalAnalyzer::program ()
{
/********************************************************************************/
/* This function will								*/
/********************************************************************************/
	lex->debug << "program function called\n";
	p2file << "program\n";
	int errors = 0;
	// token should be in the firsts of program
	// if true... keep going
	// if false...
	// Error message -
	// 	then keep going or keep getting token until token is
	// 	in the firsts of program

	// errors += define ();

	// errors += more_defines ();

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

	lex->debug << "program function returning " << errors << " errors\n";
	return errors;
}

