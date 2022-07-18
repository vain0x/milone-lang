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



LSP_SERVER := ${PWD}/target/CmdLspServer/lsp_server
TODO := ${PWD}/target/CmdSqliteTodo/todo

build: ${CAT} ${JSON_GET} ${LSP_SERVER} ${TODO}

${LSP_SERVER}: \
	CmdLspServer/milone_manifest \
	$(wildcard CmdLspServer/*.milone) \
	vendor/sqlite3/sqlite3.o
	(cd CmdLspServer; ./build)

lsp_server: ${LSP_SERVER}

test_lsp_server: ${LSP_SERVER}
	(cd CmdLspServer; env LSP_SERVER_BIN=${LSP_SERVER} ./test)

${TODO}: \
	CmdSqliteTodo/CmdSqliteTodo.milone \
	CmdSqliteTodo/milone_manifest \
	LibSqlite3/Db.milone \
	LibSqlite3/lib_sqlite3_runtime.c \
	vendor/sqlite3/sqlite3.o
	(cd CmdSqliteTodo; ./build)

todo: ${TODO}

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

run: build
	${TODO} add 'wash dishes'
	${TODO} add 'clean up table'
	${TODO}
	${TODO} remove 'wash'
	${TODO} remove 'up'
	${TODO}

test: test_cat test_json_get target/LibNurseryTests/.timestamp

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
