/*
 * Testing for the config file handling code
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glib.h>
#include <glib/gprintf.h>

#include <CUnit/Basic.h>

void test_Void() {
	CU_ASSERT(true == true);
}

void test_BasicConfigSample() {
	GKeyFile *file = g_key_file_new();
	CU_ASSERT_PTR_NOT_NULL(file);

	CU_ASSERT(TRUE == g_key_file_load_from_file(file, "config.sample.ini", G_KEY_FILE_NONE, NULL));

	char **groups = g_key_file_get_groups(file, NULL);
	CU_ASSERT_PTR_NOT_NULL(groups);

	int i = 0;
	char *group = groups[i];
	while (group != NULL) {
		group = groups[++i];
	}
	CU_ASSERT(i == 2);
	CU_ASSERT_STRING_EQUAL(groups[0], "General");
	CU_ASSERT_STRING_EQUAL(groups[1], "Account");
	g_strfreev(groups);

	CU_ASSERT(g_key_file_get_integer(file, "General", "PollInterval", NULL) == 5);
	
	CU_ASSERT_STRING_EQUAL(g_key_file_get_string(file, "Account", "ReadServer", NULL), "imap.dot.com");
	CU_ASSERT_STRING_EQUAL(g_key_file_get_string(file, "Account", "WriteServer", NULL), "smtp.dot.com");
	CU_ASSERT_STRING_EQUAL(g_key_file_get_string(file, "Account", "Username", NULL), "someguy");


	g_key_file_free(file);
}


int main() {
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Config_Suite", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (
		(NULL == CU_add_test(pSuite, "empty test", test_Void)) || 
		(NULL == CU_add_test(pSuite, "test reading config.sample", test_BasicConfigSample))
	  )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

