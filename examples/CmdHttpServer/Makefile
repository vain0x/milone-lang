# USAGE:
#	make

# Prerequisites: make, milone-lang installed

MILONE_RUNTIME := ${HOME}/.milone/runtime

default: target/serve

target/serve: target/cmd_http_server.c cmd_http_server.c
	gcc -std=gnu11 -g \
		-fsanitize=address,leak,undefined \
		-Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-label -Wno-unused-parameter -Wno-unused-but-set-parameter \
		-I ${MILONE_RUNTIME} \
		${MILONE_RUNTIME}/milone.c \
		./milone_ext.c \
		cmd_http_server.c \
		target/cmd_http_server.c \
		-o target/serve

target/cmd_http_server.c: $(shell find -type f -name '*.fs') $(shell find -type f -name '*.milone')
	mkdir -p target

	{ \
		echo '#include "${PWD}/milone_ext.h"'; \
		milone compile ${PWD}; \
	} >target/cmd_http_server.c
