default: build

MILONE := milone-dev
TRIPLET := x86_64-unknown-linux-gnu

# ------------------------------------------------
# Deps
# ------------------------------------------------

SQLITE3_O := vendor/sqlite3/sqlite3.o

${SQLITE3_O}: install-sqlite3
	./install-sqlite3

# ------------------------------------------------
# CmdCat
# ------------------------------------------------

CAT := ${PWD}/target/CmdCat/${TRIPLET}-debug/CmdCat

${CAT}: $(wildcard CmdCat/*.milone)
	milone build CmdCat

cat: ${CAT}
	cp ${CAT} cat

test_cat: ${CAT} CmdCat/test
	( cd CmdCat; CAT=${CAT} ./test )

# ------------------------------------------------
# CmdJsonGet
# ------------------------------------------------

JSON_GET := ${PWD}/target/CmdJsonGet/${TRIPLET}-debug/CmdJsonGet

${JSON_GET}: \
	$(wildcard CmdJsonGet/*.milone) \
	CmdJsonGet/milone_manifest
	milone build CmdJsonGet

json_get: ${JSON_GET}
	cp ${JSON_GET} json_get

test_json_get: ${JSON_GET} \
	CmdJsonGet/test \
	CmdJsonGet/test-expected.txt \
	CmdJsonGet/test-input.json
	( cd CmdJsonGet; JSON_GET=${JSON_GET} ./test )

# ------------------------------------------------
# CmdSqliteTodo
# ------------------------------------------------

TODO := ${PWD}/target/CmdSqliteTodo/${TRIPLET}-debug/CmdSqliteTodo

${TODO}: ${SQLITE3_O} \
	$(wildcard CmdSqliteTodo/*.milone) \
	CmdSqliteTodo/milone_manifest \
	$(wildcard LibSqlite3/*.milone) \
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
	${SQLITE3_O} \
	$(wildcard LibSqlite3/*.milone) \
	LibSqlite3/milone_manifest \
	LibSqlite3/lib_sqlite3_runtime.c
	milone run LibSqlite3 >LibSqlite3/test-output.txt

test_lib_sqlite3: \
	LibSqlite3/test-output.txt \
	LibSqlite3/test-expected.txt
	diff -q LibSqlite3/test-output.txt LibSqlite3/test-expected.txt && echo OK

# ------------------------------------------------
# CmdLspServer
# ------------------------------------------------

LSP_SERVER := ${PWD}/target/CmdLspServer/${TRIPLET}-debug/lsp_server

${LSP_SERVER}: \
	$(wildcard CmdLspServer/*.milone) \
	CmdLspServer/cmd_lsp_server_runtime.c \
	CmdLspServer/milone_manifest \
	${SQLITE3_O}
	milone build CmdLspServer

lsp_server: ${LSP_SERVER}

test_lsp_server: ${LSP_SERVER} \
	CmdLspServer/test /
	CmdLspServer/test-expected.txt
	echo 'Needs updating'
# (cd CmdLspServer; env LSP_SERVER_BIN=${LSP_SERVER} ./test)

# ------------------------------------------------
# Actions
# ------------------------------------------------

restore: \
	${SQLITE3_O}

build: \
	cat \
	json_get \
	todo

test: \
	test_cat \
	test_json_get \
	test_todo \
	test_lib_sqlite3
