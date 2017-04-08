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

