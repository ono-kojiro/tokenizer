#include "config.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inttypes.h>

#include "input.h"
#include "scanner.h"

#if USE_PARSER
#include "parser.h"
#endif

#define PRINT_TOKEN(x) { \
	fprintf(s->out, "(%s:", x); \
	fprintf(s->out, "%.*s", (int)(s->cur - s->tok), s->tok); \
	fprintf(s->out, ")"); \
}

int Scanner_Scan(INPUT *s)
{
    unsigned long u;

/*!re2c
    end = "\x00";
    eol = ([\r\n]|[\n]);
    ws  = [ \t\v]+;

    O   = [0-7];         // oct
    D   = [0-9];         // digit
    NZ  = [1-9];         // non-zero
    L   = [a-zA-Z_];     // letter
    A   = [a-zA-Z_0-9];  // alphabet
    H   = [a-fA-F0-9];   // hex
    HP  = "0" [xX];      // hex prefix
    E   = [Ee][+-]?D+;
    P   = [Pp][+-]?D+;
    FS  = ("f"|"F"|"l"|"L");     // float suffix
    IS  = ((("u"|"U")("l"|"L"|"ll"|"LL")?)|(("l"|"L"|"ll"|"LL")("u"|"U")?));
    CP  = ("u"|"U"|"L");
	SP  = ("u8"|"u"|"U"|"L");

    DBS = "\\\\"; // double backslash
	ES  = "\\"  ( [\'"?abfnrtv] | [0-7]{1,3} | "x" [a-FA-F0-9]+);
	BS  = "\x5C";  // backspace 0d92

    wd  = (A)+;
    dec = (D|NZ)+;

	any = [^];
*/


    for (;;) {
std:
		s->tok = s->cur;
        /*!re2c
            re2c:eof = 0;
            re2c:api:style = free-form;
            re2c:yyfill:enable = 1;
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "fill(s) == 0";
			
            * {
				fprintf(stderr, "(UNKNOWN:%X)", s->tok[0]);
				RET(-1);
			}
            
            $ {
				fprintf(s->out, "(EOF)\n");
				RET(EOF);
            }

			"/*" {
				goto comment_c;
			}
			
			"#" {
				goto comment_perl;
			}
			
			"//" {
				goto comment_cxx;
			}

			eol {
				fprintf(s->out, "(EOL)\n");
				continue;
			}

			end {
				fprintf(s->out, "(EOF)\n");
				RET(EOF);
			}
			
            "'\\\\'" {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			SP? "\"" ([^"])* "\"" {
				PRINT_TOKEN("STRING_LITERAL");
				return(STRING_LITERAL);
			}

			BS {
				PRINT_TOKEN("BACKSLASH");
				RET(BACKSLASH);
			}
			
            CP? "'" (ES)+ "'" {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			CP? "'" ([^'])+ "'" {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}
			
			(HP) (H)+ (IS)? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			NZ D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			"0" D* IS? {
				PRINT_TOKEN("I_CONSTANT");
				RET(I_CONSTANT);
			}

			D* "." D+ E? FS? {
				PRINT_TOKEN("F_CONSTANT");
				RET(F_CONSTANT);
			}

			dec {
				PRINT_TOKEN("DEC");
				RET(DEC);
			}
			
			wd {
				PRINT_TOKEN("WD");
				RET(WD);
			}

			ws {
				fprintf(s->out, "%.*s",
					(int)(s->cur - s->tok), s->tok);
				continue;
			}
			
			any {
				PRINT_TOKEN("ANY");
				RET(ANY);
			}
			
		*/

        /*!include:re2c "comment_c.re" */

        /*!include:re2c "comment_perl.re" */

        /*!include:re2c "comment_cxx.re" */
	}
}

