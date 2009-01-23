/*
 * imuse -- A FUSE filesystem for exposing IMAP accounts as a locally browsable filesystem, neat!
 *
 * (c) 2009 - R. Tyler Ballance <tyler@monkeypox.org>
 */

/*
 * muse_tree:
 *		Defines functions for dealing with IMAP's as a GNode-based tree
 *
 * Abstract:
 *	The basic idea is to store some basic IMAP meta-data in memory as a large GNode N-ary tree:
 *	            Accounts/
 *                |--> (d) github.com
 *                            |--> (f) NewEmail.template
 *                            |--> (d) INBOX
 *                            |         |--> (d) INBOX.other
 *                            |--> (d) Junk
 *                            |--> (d) Sent
 *                                       |--> (f) Some_Email_Subject-(2009-01-16).email
 *	
 * The file "NewEmail.template" will represent a blank email and be a "special" file, whereas the 
 * directories will be different typed nodes in the tree, files would be another node type.
 *
 * This way the FUSE integration will simply need to know how to navigate these trees and parse out 
 * pathes in such a way that it can map back to a particular level in the tree. Operations like open(2)
 * or read(2) will need to pass through to their appropriate node-type handlers (email_open(), dir_open(), 
 * and special_open())
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <glib.h>

#include "muse_tree.h"


int muse_tree_attrs_by_path(const char *path, struct stat *s) {

	return -ENOENT;
}


struct stat *default_stat(struct stat *s) {
	if (s == NULL) 
		s = (struct stat *)(malloc(sizeof(struct stat)));
	
	memset(s, 0, sizeof(struct stat));

	s->st_mode = 0;
	s->st_ino = 0;
	s->st_dev = 0;
	s->st_nlink = 0;
	s->st_uid = getuid();
	s->st_gid = getgid();
	s->st_size = 0;
	s->st_atime = time(NULL);
	s->st_mtime = time(NULL);
	s->st_ctime = time(NULL);

	return s;
}


