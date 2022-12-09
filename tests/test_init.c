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

START_TEST (mytestcase)
{
	int ret = 0;
    FILE *fp_in;

    INPUT *s = NULL;
    int got;
    
    char lines[] =
        "{\n"
        "  \"bbb\" : 1\n"
        "}\n";

    int i;
    int exp;
    int exps[] = {
        TOKEN_O_BEGIN,
        TOKEN_STRING, TOKEN_COLON, TOKEN_NUMBER,
        TOKEN_O_END
    };

#if USE_PARSER
    void *parser;
    Token token;
#endif

    fp_in = fmemopen(lines, strlen(lines), "rt");

	s = Input_Create();
	Input_Init(s);
	Input_SetStream(s, fp_in, stdout);

#if USE_PARSER
    parser = (void *)MyParserAlloc(malloc, NULL);
    MyParserInit(parser, NULL);
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
    
	Input_Delete(s);
	fclose(fp_in);

#if USE_PARSER
    MyParserFree(parser, free);
#endif

	return;
}
END_TEST

START_TEST (true_false_test)
{
	int ret = 0;
    FILE *fp_in;

    INPUT *s = NULL;
    int got;
    char lines[] =
        "[\n"
        "  true,\n"
        "  false,\n"
        "  null,\n"
        "  3.14\n"
        "]\n";

    int i;
    int exp;
    int exps[] = {
        TOKEN_A_BEGIN,
        TOKEN_TRUE, TOKEN_COMMA,
        TOKEN_FALSE, TOKEN_COMMA,
        TOKEN_NULL, TOKEN_COMMA,
        TOKEN_NUMBER,
        TOKEN_A_END
    };

    fp_in = fmemopen(lines, strlen(lines), "rt");

	s = Input_Create();
	Input_Init(s);
	Input_SetStream(s, fp_in, stdout);

    for(i = 0; i < sizeof(exps) / sizeof(exps[0]); i++){
        exp = exps[i];
        got = Scanner_Scan(s);
        PRINT_TOKEN(got, s);
        ck_assert_int_eq(got, exp);
    }
    
	Input_Delete(s);
	fclose(fp_in);

	return;
}
END_TEST


START_TEST (array_test)
{
	int ret = 0;
    FILE *fp_in;

    INPUT *s = NULL;
    int id;

    char lines[] =
        "[\n"
        "  \"aaa\"\n"
        "]\n";

    fp_in = fmemopen(lines, strlen(lines), "rt");

	s = Input_Create();
	Input_Init(s);
	Input_SetStream(s, fp_in, stdout);
	
    id = Scanner_Scan(s);
    PRINT_TOKEN(id, s);
    ck_assert_int_eq(id, TOKEN_A_BEGIN);

    id = Scanner_Scan(s);
    PRINT_TOKEN(id, s);
    ck_assert_int_eq(id, TOKEN_STRING);
    
    id = Scanner_Scan(s);
    PRINT_TOKEN(id, s);
    ck_assert_int_eq(id, TOKEN_A_END);
    
	Input_Delete(s);
	fclose(fp_in);

	return;
}
END_TEST


Suite *mysuite(void)
{
    Suite *suite;
    TCase *tc;

    suite = suite_create("MyTest");

    tc = tcase_create("Core");
    tcase_add_test(tc, mytestcase);
    suite_add_tcase(suite, tc);

    tc = tcase_create("array_test");
    tcase_add_test(tc, array_test);
    suite_add_tcase(suite, tc);
    
    tc = tcase_create("true_false_test");
    tcase_add_test(tc, true_false_test);
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

