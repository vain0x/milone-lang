default: build

.PHONY: build clean default restore run test

build: target/json_get target/todo

target/lib_json.c: LibJson/Json.milone 
	(cd LibJson; ./build)

target/json_get: \
	CmdJsonGet/CmdJsonGet.milone \
	CmdJsonGet/cmd_json_get_runtime.c \
	LibJson/lib_json_runtime.c \
	LibJson/Json.milone \
	vendor/pdjson/pdjson.o
	(cd CmdJsonGet; ./build)

target/todo: \
	CmdSqliteTodo/CmdSqliteTodo.milone \
	LibSqlite3/Db.milone \
	LibSqlite3/lib_sqlite3_runtime.c \
	vendor/sqlite3/sqlite3.o
	(cd CmdSqliteTodo; ./build)

target/lib_span_tests: \
	LibSpan/lib_span_runtime.c \
	LibSpan/lib_span_runtime.h \
	$(wildcard LibSpan/*.milone) \
	$(wildcard LibSpanTests/*.milone)
	(cd LibSpanTests; ./build)

target/lib_file_system_tests: \
	LibSpan/lib_span_runtime.c \
	LibSpan/lib_span_runtime.h \
	$(wildcard LibSpan/*.milone) \
	$(wildcard LibFileSystem/*.milone) \
	$(wildcard LibFileSystemTests/*.milone)
	(cd LibFileSystemTests; ./build)

run: build
	cat .vscode/c_cpp_properties.json | target/json_get version
	cat .vscode/c_cpp_properties.json | target/json_get configurations.length
	cat .vscode/c_cpp_properties.json | target/json_get configurations.0.name
	target/todo add 'wash dishes'
	target/todo add 'clean up table'
	target/todo
	target/todo remove 'wash'
	target/todo remove 'up'
	target/todo

test: target/lib_span_tests target/lib_file_system_tests
	if target/lib_span_tests; then echo OK; else echo FAIL=$?; fi
	if target/lib_file_system_tests; then echo OK; else echo FAIL=$?; fi

# ------------------------------------------------
# Deps
# ------------------------------------------------

restore: vendor/pdjson/pdjson.o vendor/sqlite3/sqlite3.o

vendor/pdjson/pdjson.o:
	./install-pdjson

vendor/sqlite3/sqlite3.o:
	./install-sqlite3
