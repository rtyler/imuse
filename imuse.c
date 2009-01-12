/*
 * imuse -- A FUSE filesystem for exposing IMAP accounts as a locally browsable filesystem, neat!
 *
 * (c) 2009 - R. Tyler Ballance <tyler@monkeypox.org>
 */

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


static int imuse_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else {
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
	filler(buf, "Accounts", NULL, 0);
	filler(buf, "Settings", NULL, 0);
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
	return fuse_main(argc, argv, &imuse_operations);
}

