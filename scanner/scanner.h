#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "input.h"

#define RET(x) { \
	return (x); \
}

#if USE_PARSER
#else
enum {
	DEC = 1,
	WD,
	WS,
	EOL,
	HOST,
	MACHINE,
	LOGIN,
	PASSWORD,
	METHOD,
	FIELD_NAME,
	TCHAR,
    I_CONSTANT,
    F_CONSTANT,
    STRING_LITERAL,
    BACKSLASH,
	ANY
};
#endif

int Scanner_Scan(INPUT *s);

#endif /* #ifndef SCANNER_H */


