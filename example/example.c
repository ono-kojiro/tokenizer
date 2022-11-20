#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#if USE_PARSER
#include "parser.h"
#endif

#include "scanner.h"

int main(int argc, char **argv)
{
	int ret = 0;

	int index;
	int c;
	struct option options[] = {
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
		{ "output", required_argument, 0, 'o' },
		{ "database", required_argument, 0, 'd' },
		{ 0, 0, 0, 0 }
	};

	const char *output = NULL;
	const char *input  = NULL;
	FILE *fp_out = NULL;
	FILE *fp_in  = NULL;

	INPUT *s = NULL;
	int token_id;

#if USE_PARSER
	/* Parser */
	void *parser = NULL;
	Token token;
	USERDATA *userdata = NULL;
	char buf[256];
#endif

	const char *database = NULL;

    int debug = 0;
    char *env_debug = NULL;

	while(1){
		c = getopt_long(
				argc,
				argv,
				"hvo:d:",
				options,
				&index
			);

		if(c == -1){
			break;
		}

		switch(c){
		case 'h' :
			break;
		case 'v' :
			break;
		case 'o' :
			output = optarg;
			break;
		case 'd' :
			database = optarg;
		default :
			break;
		}
	}

	if(output){
		fp_out = fopen(output, "wt");
	}
	else{
		fp_out = stdout;
	}

    env_debug = getenv("DEBUG");
    if(env_debug){
        debug = 1;
    }
    

#if USE_PARSER
	userdata = Userdata_Create();
	if(database){
		ret = Userdata_OpenDatabase(userdata, database);
	}
	else {
		ret = Userdata_OpenDatabase(userdata, ":memory:");
	}
	
	ret = Userdata_DropTable(userdata);
	ret = Userdata_CreateTable(userdata);
#endif

	while(optind < argc){
		input = argv[optind];
		fp_in = fopen(input, "rt");

		s = Input_Create();
		Input_Init(s);
		Input_SetStream(s, fp_in, fp_out);

#if USE_PARSER
		parser = (void *)MyParserAlloc(malloc, userdata);
#endif

#if USE_PARSER
		MyParserInit(parser, userdata);
#endif

#if DEBUG_PARSER
		MyParserTrace(stderr, "PARSER : ");
#endif
	
		while(1){
			token_id = Scanner_Scan(s);
			if(token_id < 0){
#if DEBUG
				fprintf(stderr, "DEBUG : %s(%d) Scanner_Scan() returned %d\n",
					__FILE__ , __LINE__ , token_id);
#endif
				break;
			}
#if DEBUG
			fprintf(stderr, "DEBUG : input is '%.*s'\n",
				(int)(s->cur - s->tok), s->tok);
#endif

#if USE_PARSER
			sprintf(buf, "%.*s", (int)(s->cur - s->tok), s->tok);
			MyParser(parser, token_id, &token);
#endif
			
		}
		
		Input_Delete(s);

#if USE_PARSER
		MyParserFree(parser, free);
#endif

		fclose(fp_in);
		optind++;
	}
		
#if USE_PARSER
	ret = Userdata_InsertRecord(userdata, "aaa", "bbb", "ccc");
	ret = Userdata_CloseDatabase(userdata);
	ret = Userdata_Delete(userdata);
#endif

	if(output){
		fclose(fp_out);
	}

	return 0;
}
