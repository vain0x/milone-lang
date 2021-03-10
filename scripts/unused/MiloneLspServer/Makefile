# USAGE:
#	make
#
# Prerequisites:
#	- gcc, milone-lang installed

default: build

.PHONY: build clean restore run

restore: vendor/pdjson vendor/sqlite3

build: target/milone_lsp_server

run: build
	./run

target/milone_lsp_server.c: $(wildcard *.fs) $(wildcard *.milone)
	./build-1 || { cat target/milone_lsp_server.c && false; }

target/milone_lsp_server: vendor/pdjson vendor/sqlite3/sqlite3.o milone_lsp_server_runtime.c target/milone_lsp_server.c
	./build-2

vendor/pdjson:
	./restore-pdjson

vendor/sqlite3:
	./restore-sqlite3

vendor/sqlite3/sqlite3.o: vendor/sqlite3
	./build-sqlite3
