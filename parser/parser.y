%include {
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sqlite3.h>

#include "token.h"

#include "userdata.h"

#include "str.h"

/* #include "parser.h" */


void token_destructor(Token *t)
{
   //fprintf(stderr, "In token_destructor t.value= %d\n", t.value);
   //fprintf(stderr, "In token_destructor t.n= %d\n", t.n);
}

} /* %include */
  

%name MyParser
%token_prefix TOKEN_

%token_type {Token*}
%default_type {Token*}
%token_destructor { token_destructor($$); }

//%extra_argument { USERDATA *userdata }
%extra_context { USERDATA *userdata }

%parse_accept
{
	fprintf(stderr, "parsing complete!\n\n\n"); 
}

%parse_failure
{
	fprintf(stderr, "parsing failed!\n\n\n");
}
   
%syntax_error {  
  fprintf(stderr, "Syntax error!\n");
  exit(1);
}   

%start_symbol input

/*  This is to terminate with a new line */
input ::= lines .

lines ::= .
lines ::= lines token .

token   ::= COMMA .
token   ::= NUMBER .
token   ::= COLON .
token   ::= A_BEGIN .
token   ::= A_END .
token   ::= O_BEGIN .
token   ::= O_END .
token   ::= STRING .
token   ::= NULL .
token   ::= TRUE .
token   ::= FALSE .
token   ::= DBL_QUOTE .
token   ::= ANY .

