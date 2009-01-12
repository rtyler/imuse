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
	return 9;
}

static int imuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fuse_info)
{
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

