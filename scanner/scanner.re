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
    DIGIT = [0-9]+;
    NUM = [1-9] DIGIT*;
    NEWLINE = [\r\n] | [\n];

    ANY = [^];
*/

    for (;;) {
std:
		s->tok = s->cur;
        /*!re2c
            re2c:api:style = free-form;
            re2c:yyfill:enable = 1;
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = s->cur;
            re2c:define:YYMARKER = s->mar;
            re2c:define:YYLIMIT = s->lim;
            re2c:define:YYFILL = "fill(s) == 0;";
			
            NEWLINE {
                RET(TK_NEWLINE);
            }

            NUM {
                RET(TK_NUM);
            }

            "+" {
                RET(TK_ADD);
            }
            
            "-" {
                RET(TK_SUB);
            }

            "*" {
                RET(TK_MUL);
            }

            "/" {
                RET(TK_DIV);
            }
            
            * {
				fprintf(stderr, "(UNKNOWN:%X)", s->tok[0]);
				RET(-1);
			}

		*/
	}
}

