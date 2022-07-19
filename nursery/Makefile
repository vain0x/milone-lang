default: build

.PHONY: build clean default restore run test cat json_get lsp_server todo

MILONE := milone-dev
TRIPLET := x86_64-unknown-linux-gnu

# ------------------------------------------------
# CmdCat
# ------------------------------------------------

CAT := ${PWD}/target/CmdCat/${TRIPLET}-debug/CmdCat

${CAT}: ${wildcard CmdCat/*.milone}
	milone build CmdCat

cat: ${CAT}
	cp ${CAT} cat

test_cat: ${CAT} CmdCat/test
	( cd CmdCat; CAT=${CAT} ./test )

# ------------------------------------------------
# CmdJsonGet
# ------------------------------------------------

JSON_GET := ${PWD}/target/CmdJsonGet/${TRIPLET}-debug/CmdJsonGet

${JSON_GET}: ${wildcard CmdJsonGet/*.milone}
	milone build CmdJsonGet

json_get: ${JSON_GET}
	cp ${JSON_GET} json_get

test_json_get: ${JSON_GET} CmdJsonGet/test
	( cd CmdJsonGet; JSON_GET=${JSON_GET} ./test )

# ------------------------------------------------
# CmdSqliteTodo
# ------------------------------------------------

TODO := ${PWD}/target/CmdSqliteTodo/${TRIPLET}-debug/CmdSqliteTodo

${TODO}: vendor/sqlite3/sqlite3.o \
	${wildcard CmdSqliteTodo/*.milone} \
	CmdSqliteTodo/milone_manifest \
	${wildcard LibSqlite3/*.milone} \
	LibSqlite3/milone_manifest \
	LibSqlite3/lib_sqlite3_runtime.c
	milone build CmdSqliteTodo

todo: ${TODO}
	cp ${TODO} todo

test_todo: ${TODO} CmdSqliteTodo/test CmdSqliteTodo/test-expected.txt
	( cd CmdSqliteTodo; TODO=${TODO} ./test )

# ------------------------------------------------
# LibSqlite3
# ------------------------------------------------

LibSqlite3/test-output.txt: \
	vendor/sqlite3/sqlite3.o \
	${wildcard LibSqlite3/*.milone} \
	LibSqlite3/milone_manifest \
	LibSqlite3/lib_sqlite3_runtime.c
	milone run LibSqlite3 >LibSqlite3/test-output.txt

test_lib_sqlite3: LibSqlite3/test-output.txt LibSqlite3/test-expected.txt
	diff -q LibSqlite3/test-output.txt LibSqlite3/test-expected.txt && echo OK



LSP_SERVER := ${PWD}/target/CmdLspServer/lsp_server

build: ${CAT} ${JSON_GET} ${LSP_SERVER} ${TODO}

${LSP_SERVER}: \
	CmdLspServer/milone_manifest \
	$(wildcard CmdLspServer/*.milone) \
	vendor/sqlite3/sqlite3.o
	(cd CmdLspServer; ./build)

lsp_server: ${LSP_SERVER}

test_lsp_server: ${LSP_SERVER}
	(cd CmdLspServer; env LSP_SERVER_BIN=${LSP_SERVER} ./test)

# target/lib_span_tests: \
# 	LibSpan/lib_span_runtime.c \
# 	LibSpan/lib_span_runtime.h \
# 	$(wildcard LibSpan/*.milone) \
# 	$(wildcard LibSpanTests/*.milone)
# 	(cd LibSpanTests; ./build)

# target/lib_file_system_tests: \
# 	LibSpan/lib_span_runtime.c \
# 	LibSpan/lib_span_runtime.h \
# 	$(wildcard LibSpan/*.milone) \
# 	$(wildcard LibFileSystem/*.milone) \
# 	$(wildcard LibFileSystemTests/*.milone)
# 	(cd LibFileSystemTests; ./build)

target/LibNurseryTests/.timestamp: \
	$(wildcard LibNursery/*.milone) \
	$(wildcard LibNurseryTests/*.milone) \
	LibNurseryTests/milone_manifest
	(cd LibNurseryTests; ./run) && \
		mkdir -p $(shell dirname $@) && \
		touch $@

test_lib_nursery: target/LibNurseryTests/.timestamp

test: test_cat test_json_get test_todo test_lib_sqlite3 target/LibNurseryTests/.timestamp

# test: target/lib_span_tests \
# 		target/lib_file_system_tests \
# 		target/LibNurseryTests/.timestamp
# 	if target/lib_span_tests; then echo OK; else echo FAIL=$?; fi
# 	if target/lib_file_system_tests; then echo OK; else echo FAIL=$?; fi

# ------------------------------------------------
# Deps
# ------------------------------------------------

restore: vendor/sqlite3/sqlite3.o

vendor/sqlite3/sqlite3.o:
	./install-sqlite3
