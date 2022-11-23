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

lines ::= EOL .
lines ::= token EOL .
lines ::= lines token EOL .

token ::= comma .
token ::= number .
token ::= colon .
token ::= a_begin .
token ::= a_end .
token ::= o_begin .
token ::= o_end .
token ::= string .
token ::= null .
token ::= true .
token ::= false .
token ::= dbl_quote .
token ::= any .

token ::= token comma .
token ::= token number .
token ::= token colon .
token ::= token a_begin .
token ::= token a_end .
token ::= token o_begin .
token ::= token o_end .
token ::= token string .
token ::= token null .
token ::= token true .
token ::= token false .
token ::= token dbl_quote .
token ::= token any .

comma   ::= COMMA .
number  ::= NUMBER .
colon   ::= COLON .
a_begin ::= A_BEGIN .
a_end   ::= A_END .
o_begin ::= O_BEGIN .
o_end   ::= O_END .
string  ::= STRING .
null    ::= NULL .
true    ::= TRUE .
false   ::= FALSE .
dbl_quote ::= DBL_QUOTE .
any     ::= ANY .

