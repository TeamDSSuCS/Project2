/********************************************************************************/
/* Project: Project 2 							        */
/* Author: David Tauraso, Lucas Winkelmann, Matthew Bennett	    		*/
/* Date: Spring 2017 								*/
/* Description:	Syntactical Analyzer for Scheme subset			        */
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
{4,3,-1,-1,-1,4,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,5,-1,5,6,6,5,5,-1,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
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
static std::map<std::string, int> action_token_to_rule = {

    {"IF_T", 19},
    {"LISTOP_T", 20},
    {"CONS_T", 21},
    {"AND_T", 22},
    {"OR_T", 23},
    {"NOT_T", 24},
    {"NUMBERP_T", 25},
    {"SYMBOLP_T", 26},
    {"LISTP_T", 27},
    {"ZEROP_T", 28},
    {"NULLP_T", 29},
    {"CHARP_T", 30},
    {"STRINGP_T", 31},
    {"PLUS_T", 32},
    {"MINUS_T", 33},
    {"DIV_T", 34},
    {"MULT_T", 35},
    {"EQUALTO_T", 36},
    {"GT_T", 37},
    {"LT_T", 38},
    {"GTE_T", 39},
    {"LTE_T", 40},
    {"IDENT_T", 41},
    {"DISPLAY_T", 42},
    {"NEWLINE_T", 43},

};


SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename) {
/********************************************************************************/
/* This function will open a file and start our syntactical analyzer		*/
/********************************************************************************/
  lex = new LexicalAnalyzer (filename);
  int fnlength = strlen (filename);
  filename[fnlength-2] = 'p';
  filename[fnlength-1] = '2';
  p2file.open (filename);
  int errors = program ();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
/********************************************************************************/
/* This function will close our file and delete our object			*/
/********************************************************************************/
    p2file.close();
    delete lex;
}

int SyntacticalAnalyzer::action(int current_rule) {
  // The first tokens for each action rule has already been read in
  // this function reads in one token for stmt
  int errors = 0;
  token = lex->GetToken();
  p2file << "Starting <action>. Current token = " << lex->GetTokenName(token) << endl;
  current_rule = action_token_to_rule.find(lex->GetTokenName(token))->second;
  p2file << "Using rule " << current_rule << endl;
  switch(current_rule) {
  case 19:
    if(lex->GetTokenName(token) != "IF_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    errors += stmt(4);
    errors += else_part(9);
    break;
    
  case 20:
    if(lex->GetTokenName(token) != "LISTOP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 21:
    if(lex->GetTokenName(token) != "CONS_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    errors += stmt(4);
    break;
  case 22:
    if(lex->GetTokenName(token) != "AND_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 23:
    if(lex->GetTokenName(token) != "OR_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 24:
    if(lex->GetTokenName(token) != "NOT_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 25:
    if(lex->GetTokenName(token) != "NUMBERP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 26:
    if(lex->GetTokenName(token) != "SYMBOLP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 27:
    if(lex->GetTokenName(token) != "LISTP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 28:
    if(lex->GetTokenName(token) != "ZEROP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 29:
    if(lex->GetTokenName(token) != "NULLP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
      break;
  case 30:
    if(lex->GetTokenName(token) != "CHARP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 31:
    if(lex->GetTokenName(token) != "STRINGP_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 32:
    if(lex->GetTokenName(token) != "PLUS_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 33:
    if(lex->GetTokenName(token) != "MINUS_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    errors += stmt_list(3);
    break;
  case 34:
    if(lex->GetTokenName(token) != "DIV_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    errors += stmt_list(3);
    break;
  case 35:
    if(lex->GetTokenName(token) != "MULT_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 36:
    if(lex->GetTokenName(token) != "EQUALTO_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 37:
    if(lex->GetTokenName(token) != "GT_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 38:
    if(lex->GetTokenName(token) != "LT_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 39:
    if(lex->GetTokenName(token) != "GTE_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 40:
    if(lex->GetTokenName(token) != "LTE_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 41:
    if(lex->GetTokenName(token) != "IDENT_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt_list(3);
    break;
  case 42:
    if(lex->GetTokenName(token) != "DISPLAY_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    errors += stmt(4);
    break;
  case 43:
    if(lex->GetTokenName(token) != "NEWLINE_T")
      p2file << "error" << endl;
    token = lex->GetToken();
    break;
  } 
  p2file << "Ending <action>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  token = lex->GetToken();
  return errors;
}

int SyntacticalAnalyzer::stmt_list(int current_rule) {
  // There are no terminals to read in for the stmt_list rules so call the function
  // representing the next rule
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
  case 6: 
    break;
  }
  p2file << "Ending <stmt_list>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::param_list(int current_rule) {
  // IDENT_T should have already been collected
  int errors = 0;
  p2file << "Starting <param_list>. Current token = " << lex->GetTokenName(token) << endl;
  if (lex->GetTokenName(token) == "RPAREN_T") {
    p2file << "Using rule 16" << endl;
  } else {
    token = lex->GetToken();
    p2file << "Using rule 15" << endl;
    errors += param_list(8);
  }
  p2file << "Ending <param_list>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::else_part(int current_rule)
{
  // Any token collected in caller of else_part has already collected a token from stmt
  // don't collect any tokens
  int errors = 0;
  p2file << "Starting <else_part>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 17: {
    {
      errors += stmt(4);
      break;
    }
    case 18:
      {
	break;
      }
  }
  }
  p2file << "Ending <else_part>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::define(int current_rule) {
  // Starts collecting tokens.
  // Collects token for param_list so param_list won't collect a token in any of the rules it
  // represents
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
  return errors;
}

int SyntacticalAnalyzer::more_tokens(int current_rule) {
  // The first token for the rules of any_other_token has already been collected
  // don't need to collect any tokens
  int errors = 0;
  p2file << "Starting <more_tokens>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 13: { 
    errors += any_other_token(11);
    errors += more_tokens(7);
    break;
  }
  case 14: {
    break;
  }
  }
  p2file << "Ending <more_tokens>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::any_other_token(int current_rule) {
  // The token has already been collected by whomever called more_tokens except for rule 44
  // only need to collect token for rule 44
  int errors = 0;
  p2file << "Starting <any_other_token>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 44: {
    token = lex->GetToken();
    errors += more_tokens(7);
    break;
  }
  default:
    break;
  }
  token = lex->GetToken();
  p2file << "Ending <any_other_token>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::quoted_lit(int current_rule) {
  // The token has not been collected for any_other_token so collect a token
  // then call any_other_token
  int errors = 0;
  token = lex->GetToken();
  p2file << "Starting <quoted_lit>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 12: 
    errors += any_other_token(11);
    break;
  }
  p2file << "Ending <quoted_lit>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::literal(int current_rule) {
  // The first token for literal has already been collected
  // only need to collect for rule 10
  int errors = 0;
  p2file << "Starting <literal>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 11:
    errors += quoted_lit(6);
    break;
  case 10:
    token = lex->GetToken();
    break;
  }
  p2file << "Ending <literal>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::more_defines(int current_rule) {
  // The first token for define has already been collected
  // no need to collect a token for define and more_defines
  int errors = 0;
  p2file << "Starting <more_defines>. Current token = " << lex->GetTokenName(token) << endl;
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << endl;
  switch(next_rule) {
  case 3:
    errors += define(1);
    errors += more_defines(2);
    break;
  }
  p2file << "Ending <more_defines>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::stmt(int current_rule) {
  // LPAREN_T has already been collected
  // no need to collect any token except for rule 8
  int errors = 0;
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
  case 8:
    token = lex->GetToken();
    break;
  } 
  p2file << "Ending <stmt>. Current token = " << lex->GetTokenName(token) << ". Errors = " << errors << endl;
  return errors;
}

int SyntacticalAnalyzer::program ()
{
/********************************************************************************/
/* This function will begin our syntactical analyzer calls according to our     */
/* grammar								        */
/********************************************************************************/
  lex->debug << "program function called\n";
  int errors = 0;
  // dfa evaluator
  // token should be in the firsts of program
  // if true... keep going
  // if false...
  // Error message -
  // 	then keep going or keep getting token until token is
  // 	in the firsts of program
  
  p2file << "Starting <program>. ";
  int current_rule = 0;
  token = lex->GetToken();
  p2file << "Current token = " << lex->GetTokenName(token)<< endl; 
  int next_rule = ll1table[current_rule][token_to_col.find(lex->GetTokenName(token))->second];
  p2file << "Using rule " << next_rule << std::endl;
  switch(next_rule) {
  case 1: {
    errors += define(next_rule);
    errors += more_defines(2);
    p2file << "Ending <program>. Current token = " << lex->GetTokenName(token) << ". Errors = "<< errors << endl;
    break;
  }
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
  
  lex->debug << "program function returning " << errors << " errors\n";
  return errors;
}

