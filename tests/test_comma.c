#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <getopt.h>

#if USE_PARSER
#include "parser.h"
#endif

#include "scanner.h"

#include <check.h>

#define PRINT_TOKEN(id, s) \
    fprintf(stderr, "%d : '%.*s'\n", \
        id, \
        (int)(s->cur - s->tok), s->tok)

#undef PRINT_TOKEN
#define PRINT_TOKEN

START_TEST (test_comma)
{
	int ret = 0;
    FILE *fp_in;

    INPUT *s = NULL;
    int got;
    
    char lines[] = " \
[ \
  \"aaa\" , \
  \"bbb\" , \
  \"ccc\" , \
]";

    int i;
    int exp;
    int exps[] = {
        TOKEN_A_BEGIN,
        TOKEN_STRING, TOKEN_COMMA,
        TOKEN_STRING, TOKEN_COMMA,
        TOKEN_STRING, TOKEN_COMMA,
        TOKEN_A_END
    };

#if USE_PARSER
    void *parser = NULL;
    Token token;
    USERDATA *userdata = NULL;
#endif

    fp_in = fmemopen(lines, strlen(lines), "rt");

	s = Input_Create();
	Input_Init(s);
	Input_SetStream(s, fp_in, stdout);

#if USE_PARSER
    userdata = (USERDATA *)Userdata_Create();
    
    parser = (void *)MyParserAlloc(malloc, userdata);
    MyParserInit(parser, userdata);
    MyParserTrace(stderr, "PARSER : ");

#endif

    for(i = 0; i < sizeof(exps) / sizeof(exps[0]); i++){
        exp = exps[i];
        got = Scanner_Scan(s);
        PRINT_TOKEN(got, s);
        ck_assert_int_eq(got, exp);

#if USE_PARSER
        MyParser(parser, got, &token);
#endif
    }

    MyParser(parser, 0, &token);
    ck_assert_int_eq(userdata->accept, 1);
    
    
	Input_Delete(s);
	fclose(fp_in);

#if USE_PARSER
    MyParserFinalize(parser);
    MyParserFree(parser, free);
    Userdata_Delete(userdata);
#endif

	return;
}
END_TEST

Suite *mysuite(void)
{
    Suite *suite;
    TCase *tc;

    suite = suite_create("MyTest");

    tc = tcase_create("Additional Comma");
    tcase_add_test(tc, test_comma);
    suite_add_tcase(suite, tc);

    return suite;
}

int main(int argc, char **argv)
{
   int number_failed;
   Suite *s;
   SRunner *sr;

   s = mysuite();
   sr = srunner_create(s);

   srunner_run_all(sr, CK_NORMAL);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

