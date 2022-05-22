# USAGE:
#    To build `cat` command:
#    $ make
#    To test:
#    $ make test

CC ?= gcc
MILONE_HOME := ${PWD}/../..

default: test
.PHONY: default test

test: cat
	./test

cat: cmd_cat.c ${wildcard *.milone} milone_manifest
	MILONE_HOME=${MILONE_HOME} milone build ${PWD} -o cat
