# USAGE:
#	make

# Prerequisites: make, milone-lang installed

CC ?= gcc
MILONE_RUNTIME := ${HOME}/.milone/runtime

default: target/serve

target/serve: target/cmd_http_server.c cmd_http_server.c
	${CC} -std=gnu11 -g \
		-fsanitize=address \
		-Wall \
		-Wextra \
		-Wno-parentheses-equality \
		-Wno-pointer-to-int-cast \
		-Wno-unknown-warning-option \
		-Wno-unused-but-set-variable \
		-Wno-unused-const-variable \
		-Wno-unused-label \
		-Wno-unused-parameter \
		-Wno-unused-variable \
		-I${MILONE_RUNTIME} \
		${MILONE_RUNTIME}/milone.c \
		milone_ext.c \
		cmd_http_server.c \
		target/cmd_http_server.c \
		-o target/serve

target/cmd_http_server.c: $(shell find -type f -name '*.fs') $(shell find -type f -name '*.milone')
	mkdir -p target

	{ \
		echo '#include "${PWD}/milone_ext.h"'; \
		milone compile ${PWD}; \
	} >target/cmd_http_server.c
