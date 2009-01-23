/*
 * imuse -- A FUSE filesystem for exposing IMAP accounts as a locally browsable filesystem, neat!
 *
 * (c) 2009 - R. Tyler Ballance <tyler@monkeypox.org>
 */

#ifndef __MUSE_TREE_H
#define __MUSE_TREE_H

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NODE_TYPE_EMAIL   1334
#define NODE_TYPE_DIR	  1335
#define NODE_TYPE_FILE	  1336
#define NODE_TYPE_SPECIAL 1337

struct muse_tree_node {
	unsigned int type;
	char *display_name; 
	struct stat *st;
	void *node_data;
};

struct muse_tree_email_node;
struct muse_tree_dir_node;
struct must_tree_file_node;
struct muse_tree_special_node;

extern struct stat *default_stat(struct stat *);
extern int muse_tree_attrs_by_path(const char *, struct stat *);


#endif
