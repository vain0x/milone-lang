default: build

.PHONY: build clean deafult restore run

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

# ------------------------------------------------
# Deps
# ------------------------------------------------

restore: vendor/pdjson/pdjson.o vendor/sqlite3/sqlite3.o

vendor/pdjson/pdjson.o:
	./install-pdjson

vendor/sqlite3/sqlite3.o:
	./install-sqlite3
