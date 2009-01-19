# Standard definitions
CC   	?= gcc
TAR	?= tar
RM	?= -rm
CFLAGS	:= -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=22  -ggdb `pkg-config --cflags glib-2.0`
LDFLAGS := -lfuse -lcunit -lncurses `pkg-config --libs glib-2.0` -lssl -lpam -lc-client

# "Quiet printing"
ifdef V
  ifeq ("$(origin V)", "command line")
    Q =
  endif
endif
ifndef V
  Q = @
endif
QUIET_CC   = $(Q:@=@echo	'     CC        '$@;)
QUIET_LINK = $(Q:@=@echo	'     LINK      '$@;)
QUIET_AR   = $(Q:@=@echo	'     AR        '$@;)
QUIET_RM   = $(Q:@=@echo	'     RM        '$(OBJS);)

# Debug support
ifdef D
  ifeq ("$(origin D)", "command line")
    CFLAGS+=-DDEBUG
  endif
endif

%.o: %.c
	$(QUIET_CC)$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(QUIET_RM)$(RM) $(OBJS)

really_clean: clean
	$(QUIET_RM)$(RM) $(OUT) $(OUT).tar
