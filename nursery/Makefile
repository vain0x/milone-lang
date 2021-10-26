default: build

.PHONY: build clean default restore run test json_get todo

JSON_GET := target/CmdJsonGet/json_get
TODO := target/CmdSqliteTodo/todo

build: ${JSON_GET} ${TODO}

target/lib_json.c: LibJson/Json.milone 
	(cd LibJson; ./build)

${JSON_GET}: \
	CmdJsonGet/CmdJsonGet.milone \
	CmdJsonGet/cmd_json_get_runtime.c \
	LibJson/lib_json_runtime.c \
	LibJson/Json.milone \
	vendor/pdjson/pdjson.o
	(cd CmdJsonGet; ./build)

json_get: ${JSON_GET}

${TODO}: \
	CmdSqliteTodo/CmdSqliteTodo.milone \
	LibSqlite3/Db.milone \
	LibSqlite3/lib_sqlite3_runtime.c \
	vendor/sqlite3/sqlite3.o
	(cd CmdSqliteTodo; ./build)

todo: ${TODO}

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

target/LibNurseryTests/.timestamp: \
	$(wildcard LibNursery/*.milone) \
	$(wildcard LibNurseryTests/*.milone)
	(cd LibNurseryTests; ./run) && \
		mkdir -p $(shell dirname $@) && \
		touch $@

test_lib_nursery: target/LibNurseryTests/.timestamp

run: build
	cat .vscode/c_cpp_properties.json | ${JSON_GET} version
	cat .vscode/c_cpp_properties.json | ${JSON_GET} configurations.length
	cat .vscode/c_cpp_properties.json | ${JSON_GET} configurations.0.name
	${TODO} add 'wash dishes'
	${TODO} add 'clean up table'
	${TODO}
	${TODO} remove 'wash'
	${TODO} remove 'up'
	${TODO}

test: target/lib_span_tests \
		target/lib_file_system_tests \
		target/LibNurseryTests/.timestamp
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
