/*
 * imuse -- A FUSE filesystem for exposing IMAP accounts as a locally browsable filesystem, neat!
 *
 * (c) 2009 - R. Tyler Ballance <tyler@monkeypox.org>
 */

#ifndef __MUSE_SEND_H
#define __MUSE_SEND_H

struct muse_send_config {
	char *hostname;
	char *sender_handle;
	char *sender_host;
	long options;
};

extern struct muse_send_config *config_by_account;


#endif
