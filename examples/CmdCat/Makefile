# USAGE:
#    To build `cat` command:
#    $ make
#    To test:
#    $ make test

MILONE_RUNTIME := ${HOME}/.milone/runtime

cat: cmd_cat.generated.c cmd_cat.c
	gcc -std=c11 -g \
		-Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-label -Wno-unused-parameter -Wno-unused-but-set-parameter \
		-I ${MILONE_RUNTIME} \
		${MILONE_RUNTIME}/milone.c \
		cmd_cat.c \
		cmd_cat.generated.c \
		-o cat

cmd_cat.generated.c: *.fs
	milone compile ${PWD} >cmd_cat.generated.c

test: cat
	./test
