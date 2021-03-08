default: build

.PHONY: build clean deafult restore run

build: target/json_get

target/lib_json.c: LibJson/Json.milone 
	(cd LibJson; ./build)

target/json_get: \
	CmdJsonGet/CmdJsonGet.milone \
	CmdJsonGet/cmd_json_get_runtime.c \
	LibJson/lib_json_runtime.c \
	LibJson/Json.milone \
	vendor/pdjson/pdjson.o
	(cd CmdJsonGet; ./build)

run: target/json_get
	cat .vscode/c_cpp_properties.json | target/json_get version
	cat .vscode/c_cpp_properties.json | target/json_get configurations.length
	cat .vscode/c_cpp_properties.json | target/json_get configurations.0.name

# ------------------------------------------------
# Deps
# ------------------------------------------------

restore: vendor/pdjson/pdjson.o

vendor/pdjson/pdjson.o:
	./install-pdjson
