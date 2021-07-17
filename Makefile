# Makefile as a thin wrapper of MyBuildTool.
#
# USAGE:
#    make
#    make install
#    make install-dev

default: test

.PHONY: build clean default install install-dev test uninstall

# ------------------------------------------------
# entrypoints
# ------------------------------------------------

clean:
	scripts/clean

install:
	scripts/install

install-dev:
	scripts/install-dev

uninstall:
	scripts/uninstall

# ------------------------------------------------
# misc
# ------------------------------------------------

bin/ninja:
	scripts/install-ninja

# ------------------------------------------------
# MyBuildTool wrapper
# ------------------------------------------------

MY_BUILD := scripts/MyBuildTool/bin/Debug/net5.0/MyBuildTool
MY_BUILD_TIMESTAMP := target/.timestamp/my_build_tool

.PHONY: dotnet_restore gen2 gen3 integration_tests my_build self test_self

target/.timestamp/dotnet_restore: \
		$(wildcard **/*.fsproj)
	dotnet restore && mkdir -p $(shell dirname $@) && touch $@

${MY_BUILD_TIMESTAMP}: target/.timestamp/dotnet_restore \
		$(wildcard scripts/MyBuildTool/*.fs) \
		$(wildcard scripts/MyBuildTool/*.fsproj)
	dotnet build -nologo scripts/MyBuildTool && mkdir -p $(shell dirname $@) && touch $@

my_build: ${MY_BUILD_TIMESTAMP}

target/milone: bin/ninja ${MY_BUILD_TIMESTAMP} \
		runtime/milone.h \
		runtime/milone.c \
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
		$(wildcard tests/**/*.fs) \
		$(wildcard tests/**/*.milone) \
		$(wildcard tests/**/*.output)
	${MY_BUILD} tests && mkdir -p $(shell dirname $@) && touch $@

integration_tests: target/.timestamp/integration_tests

test: test_self integration_tests
