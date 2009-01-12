/*
 * imuse -- A FUSE filesystem for exposing IMAP accounts as a locally browsable filesystem, neat!
 *
 * (c) 2009 - R. Tyler Ballance <tyler@monkeypox.org>
 */

#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include <glib.h>

#include "imapper.h"

static GHashTable *__special_directories = NULL;
struct stat *default_stat_entry(struct stat *stat_defaults) 
{
	if (stat_defaults)
		memset(stat_defaults, 0, sizeof(struct stat));
	else
		stat_defaults = malloc(sizeof(struct stat));
	stat_defaults->st_mode = 0;
	stat_defaults->st_ino = 0;
	stat_defaults->st_dev = 0;
	stat_defaults->st_nlink = 0;
	stat_defaults->st_uid = getuid();
	stat_defaults->st_gid = getgid();
	stat_defaults->st_size = 0;
	stat_defaults->st_atime = time(NULL);
	stat_defaults->st_mtime = time(NULL);
	stat_defaults->st_ctime = time(NULL);

	return stat_defaults;
}

static int imuse_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;
	stbuf = default_stat_entry(stbuf);

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else {
		++path;
		GList *rc = g_list_find(g_hash_table_get_keys(__special_directories), path);
		if (rc) {
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
			return 0;
		}
		return -ENOENT;
	}
	return 0;
}

static int imuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fuse_info)
{
	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	GList *keys = g_hash_table_get_keys(__special_directories);
	GList *key = g_list_first(keys);
	do {
		filler(buf, key->data, NULL, 0);
	} while(key = g_list_next(key));
	return 0;
}

static int imuse_open(const char *path, struct fuse_file_info *fuse_info)
{
	return 0;
}

static int imuse_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fuse_info)
{
	return 0;
}

static struct fuse_operations imuse_operations = { .getattr = imuse_getattr, .readdir = imuse_readdir, .open = imuse_open, .read = imuse_read };

int main(int argc, char *argv[])
{
	__special_directories = g_hash_table_new(NULL, g_str_equal);
	/* Our keys will eventually turn into "special properties" about our make believe directories */
	g_hash_table_insert(__special_directories, "Accounts", g_hash_table_new(NULL, NULL));
	g_hash_table_insert(__special_directories, "Settings", g_hash_table_new(NULL, NULL));

	return fuse_main(argc, argv, &imuse_operations);
}

