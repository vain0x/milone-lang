# Makefile as a thin wrapper of MyBuildTool.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: test

.PHONY: build clean default install install-dev pack test uninstall

clean:
	scripts/clean

install-dev:
	scripts/install-dev

# ------------------------------------------------
# misc
# ------------------------------------------------

bin/ninja:
	scripts/install-ninja

runtime/hashmap.h:
	scripts/install-hashmap

# ------------------------------------------------
# MyBuildTool wrapper
# ------------------------------------------------

MY_BUILD := scripts/MyBuildTool/bin/Debug/net6.0/MyBuildTool
MY_BUILD_TIMESTAMP := target/.timestamp/my_build_tool

.PHONY: dotnet_restore gen2 gen3 integration_tests my_build self test_self

target/.timestamp/dotnet_restore: \
		$(shell find src milone_libs -maxdepth 3 -name '*.fsproj')
	dotnet restore && mkdir -p $(shell dirname $@) && touch $@

${MY_BUILD_TIMESTAMP}: target/.timestamp/dotnet_restore \
		$(wildcard scripts/MyBuildTool/*.fs) \
		$(wildcard scripts/MyBuildTool/*.fsproj)
	dotnet build -nologo scripts/MyBuildTool && mkdir -p $(shell dirname $@) && touch $@

my_build: ${MY_BUILD_TIMESTAMP}

install: ${MY_BUILD_TIMESTAMP}
	${MY_BUILD} self-install

uninstall: ${MY_BUILD_TIMESTAMP}
	${MY_BUILD} self-uninstall

pack: ${MY_BUILD_TIMESTAMP}
	${MY_BUILD} pack

target/milone: bin/ninja ${MY_BUILD_TIMESTAMP} \
		runtime/hashmap.h \
		runtime/milone.h \
		runtime/milone.c \
		runtime/milone_platform.c \
		$(wildcard milone_libs/*/*.fs) \
		$(wildcard milone_libs/*/*.milone) \
		$(wildcard src/*/*.fs) \
		$(wildcard src/*/*.fsproj) \
		$(wildcard src/*/*.milone)
	${MY_BUILD} gen2 && mkdir -p $(shell dirname $@) && touch $@

gen2: target/milone

target/.timestamp/gen3: bin/ninja ${MY_BUILD_TIMESTAMP} target/milone
	${MY_BUILD} gen3 && mkdir -p $(shell dirname $@) && touch $@

gen3: target/.timestamp/gen3

self: gen2

test_self: gen3

target/.timestamp/integration_tests: bin/ninja ${MY_BUILD_TIMESTAMP} target/milone \
		$(shell find tests -type f -mtime -1)
	${MY_BUILD} tests && mkdir -p $(shell dirname $@) && touch $@

integration_tests: target/.timestamp/integration_tests

test: test_self integration_tests
