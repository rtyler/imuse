/*
 * Testing for the smtp sending code
 */
#include <stdio.h>
#include <glib.h>
#include <imap/c-client.h>

#include <CUnit/Basic.h>

#define SMTP_HOST "smtp.dot.com"
#define SMTP_RECIP "imuse@dot.com"


void mm_flags(MAILSTREAM *stream, unsigned long number) { printf("Calling mm_flags\n"); return; }
void mm_status(MAILSTREAM *stream, char *mailbox, MAILSTATUS *status) { printf("Calling mm_status\n"); return; }
void mm_searched(MAILSTREAM *stream, unsigned long number) { printf("Calling mm_searched\n"); return; }
void mm_exists(MAILSTREAM *stream, unsigned long number) { printf("Calling mm_exists\n"); return; }
void mm_expunged(MAILSTREAM *stream, unsigned long number) { printf("Calling mm_expunged\n"); return; }
void mm_list(MAILSTREAM *stream, int delim, char *name, long attrib) { printf("Calling mm_list\n"); return; }
void mm_log(char *string,long errflg) { 
	printf("==(mm_log)==> %s\n", string);
	return; 
}
void mm_lsub(MAILSTREAM *stream,int delimiter,char *name,long attributes) { printf("Calling mm_lsub\n"); return; }
void mm_fatal(char *string) { printf("Calling mm_fatal\n"); return; }
long mm_diskerror(MAILSTREAM *stream,long errcode,long serious) { printf("Calling mm_diskerror\n"); return 0L; }
void mm_dlog(char *string) { 
	printf("==(mm_dlog)==> %s\n", string);
	return;
}
void mm_notify(MAILSTREAM *stream,char *string,long errflg) { printf("Calling mm_notify\n"); return; }
void mm_critical(MAILSTREAM *stream) { printf("Calling mm_critical\n"); return; }
void mm_nocritical(MAILSTREAM *stream) { printf("Calling mm_nocritical\n"); return;}
void mm_login(NETMBX *mb,char *user,char *pwd,long trial) { printf("Calling mm_login\n"); return; }

void test_Void() {
	CU_ASSERT(TRUE == TRUE);
}

void test_BasicSendMail() {
	char *server = SMTP_HOST;
	char *recip = SMTP_RECIP;
	long smtp_options = 0L;

	if (getenv("SMTP_HOST") && getenv("SMTP_RECIP")) {
		server = getenv("SMTP_HOST");
		recip = getenv("SMTP_RECIP");
	}

	CU_ASSERT_STRING_NOT_EQUAL_FATAL(server, SMTP_HOST);
	CU_ASSERT_STRING_NOT_EQUAL_FATAL(recip, SMTP_RECIP);

	char *servers[] = {server};
	SENDSTREAM *stream = smtp_open(servers, smtp_options);
	CU_ASSERT_PTR_NOT_NULL(stream);

	char *name = "Unit Tester";
	char *sender_email = "imuse-unit-test";
	char *sender_host = mylocalhost();
	char *bodytext = (char *)(fs_get(8*MAILTMPLEN));

	ENVELOPE *envelope = mail_newenvelope();
	BODY *body = mail_newbody();
	
	envelope->from = mail_newaddr();
	envelope->from->personal = cpystr(name);
	envelope->from->mailbox = cpystr(sender_email);
	envelope->from->host = cpystr(sender_host);

	envelope->return_path = mail_newaddr();
	envelope->return_path->mailbox = cpystr(sender_email);
	envelope->return_path->host = cpystr(sender_host);

	rfc822_parse_adrlist(&envelope->to, cpystr(recip), sender_host);

	envelope->subject = cpystr("test_BasicSendMail");

	body->type = TYPETEXT;

	snprintf(bodytext, (8*MAILTMPLEN), "This is a simple text body");

	body->contents.text.data = (unsigned char *)(bodytext);
	body->contents.text.size = strlen(bodytext);

	envelope->date = (char *)(fs_get(1 + MAILTMPLEN));
	rfc822_date(envelope->date);

	if (stream) {
		printf("Sending...\n");
		if (smtp_mail(stream, "MAIL", envelope, body)) {
			printf("Okay, %s\n", stream->reply);
		}
		else {
			printf("Fail, %s\n", stream->reply);
		}
	}

	mail_free_envelope(&envelope);
	mail_free_body(&body);
	if (stream) {
		smtp_close(stream);
	}
}

int main() {
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Smtp_Suite", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (
		(NULL == CU_add_test(pSuite, "empty test", test_Void)) ||
		(NULL == CU_add_test(pSuite, "sending a basic email", test_BasicSendMail))
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

